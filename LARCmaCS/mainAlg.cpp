#include "mainAlg.h"
#include <iostream>
#include <fstream>
//#include <TCHAR.H>
#include <windows.h>
//#include <process.h>

using namespace std;

int initConfig(RCConfig *config){
    ifstream configFile;
    string line;

    configFile.open("LARCmaCS.cnf", ios::in);

    if(!configFile.is_open()) {
        cerr << "Can't open configuration file" << endl;
        return -1;
    }

    if(!config) {
        cerr << "Can't parse configuration file" << endl;
        return -2;
    }

    while(!configFile.eof()){
        getline(configFile, line);

        if(line.empty())
            continue;

        if(line.find("rfclient.name") != string::npos) {
            config->name = line.substr(line.find('=') + 1);

            if(config->name.size() > 16) {
                cerr << "[WARNING] rfclient.name value is too long." << endl << "It will be truncated up to 16 characters." << endl;
                config->name.resize(16);
            }
        }

        if(line.find("rfclient.file_of_matlab") != string::npos) {
            string fom = line.substr(line.find('=') + 1);

            if(fom.size() > 16) {
                cerr << "[WARNING] rfclient.file_of_matlab value is too long." << endl << "It will be truncated up to 16 characters." << endl;
                fom.resize(16);
            }
            char *str = new char[fom.length() + 1];
            strcpy(str, fom.c_str());
            config->file_of_matlab = str;
        }

        if(line.find("rfclient.RULE_AMOUNT") != string::npos){
            config->RULE_AMOUNT = atoi(line.substr(line.find('=') + 1).c_str());
        }

        if(line.find("rfclient.RULE_LENGTH") != string::npos){
            config->RULE_LENGTH = atoi(line.substr(line.find('=') + 1).c_str());
        }

        if(line.find("rfclient.BACK_AMOUNT") != string::npos){
            config->BACK_AMOUNT = atoi(line.substr(line.find('=') + 1).c_str());
        }

        if(line.find("rfclient.BACK_LENGTH") != string::npos){
            config->BACK_LENGTH = atoi(line.substr(line.find('=') + 1).c_str());
        }
    }

    configFile.close();

    return 0;
}

void MainAlgWorker::init(){
    RCConfig rcconfig;

    cout << "Initialization config file..." << endl;

    if(!initConfig(&rcconfig)) {
        cout << rcconfig.file_of_matlab << endl;
        cout << rcconfig.name << endl;
        cout << rcconfig.BACK_AMOUNT << endl;
        cout << rcconfig.BACK_LENGTH << endl;
        cout << rcconfig.RULE_AMOUNT << endl;
        cout << rcconfig.RULE_LENGTH << endl;

        cout << "...successful" << endl;
    }
    else {
        cerr << "...bad" << endl;
        char *str = new char[16];
        str = "Robofootball";
        rcconfig.name = str;
        str = "main";
        rcconfig.file_of_matlab=str;
        rcconfig.RULE_AMOUNT=5;
        rcconfig.RULE_LENGTH=5;
        rcconfig.BACK_AMOUNT=10;
        rcconfig.BACK_LENGTH=8;

    }

    MlData mtl(rcconfig);
    fmldata = mtl;

    run_matlab();
}

void MainAlgWorker::run_matlab()
{
    cout << "Work is started..." << endl;

    if (!(fmldata.ep = engOpen(NULL))) {
        cerr << "Can't open Matlab Engine" << endl;
        fmtlab = false;
        return;
    }

    m_buffer[255] = '\0';
    engOutputBuffer(fmldata.ep, m_buffer, 255);

    // Path_Of_Files
    TCHAR CurrentPath[MAX_PATH];
    char StringWithPath[MAX_PATH],StringPath[MAX_PATH];

    // Detecting Directory
    printf("Matlab Engine is opened\nStart to detect directory\n");
    GetCurrentDirectory(sizeof(CurrentPath), CurrentPath);

#ifdef UNICODE
    wcstombs(StringPath, CurrentPath, MAX_PATH - 1);
#else
    CharToOem(StringPath, CurrentPath);
#endif

    sprintf(StringWithPath, "cd %s;", StringPath);
    engEvalString(fmldata.ep, StringWithPath);
    printf("We are on %s\n",StringWithPath);

    //-----create Rules-----
    char sendString[256];
    sprintf (sendString, "Rules=zeros(%d, %d)", fmldata.config.RULE_AMOUNT, fmldata.config.RULE_LENGTH);
    engEvalString(fmldata.ep, sendString);
    engEvalString(fmldata.ep, "disp(1)");

    fmtlab = true;
}

void MainAlgWorker::stop_matlab()
{
    fmtlab = false;
}


void MainAlgWorker::run(PacketSSL packetssl)
{
    t = clock();
    Time_count++;
//    if(!shutdowncomp && fmtlab)
//        cout << "Packet is received!" << endl;

    // [Start] Debug printing arrays from pocketssl
//    cout << "Balls array is: ";
//    for (int i = 0; i < sizeof(packetssl.balls) / sizeof(packetssl.balls[0]); i++)
//        cout << packetssl.balls[i] << " # ";
//    cout << endl;

//    cout << "Blues array is: ";
//    for (int i = 0; i < sizeof(packetssl.robots_blue) / sizeof(packetssl.robots_blue[0]); i++)
//        cout << packetssl.robots_blue[i] << " | ";
//    cout << endl;

//    cout << "Yellows array is: ";
//    for (int i = 0; i < sizeof(packetssl.robots_yellow) / sizeof(packetssl.robots_yellow[0]); i++)
//        cout << packetssl.robots_yellow[i] << " # ";
//    cout << endl;
    // [End] Debug printing arrays from pocketssl

    memcpy(mxGetPr(fmldata.Ball), packetssl.balls, BALL_COUNT_d);
    memcpy(mxGetPr(fmldata.Blue), packetssl.robots_blue, TEAM_COUNT_d);
    memcpy(mxGetPr(fmldata.Yellow), packetssl.robots_yellow, TEAM_COUNT_d);

    engPutVariable(fmldata.ep, "Balls", fmldata.Ball);
    engPutVariable(fmldata.ep, "Blues", fmldata.Blue);
    engPutVariable(fmldata.ep, "Yellows", fmldata.Yellow);

    engEvalString(fmldata.ep, fmldata.config.file_of_matlab);

    fmldata.Rule = engGetVariable(fmldata.ep, "Rules");

    char sendString[256];
    sprintf(sendString, "Rules=zeros(%d, %d);", fmldata.config.RULE_AMOUNT, fmldata.config.RULE_LENGTH);
    engEvalString(fmldata.ep, sendString);

    double *ruleArray = (double *)malloc(fmldata.config.RULE_AMOUNT * fmldata.config.RULE_LENGTH * sizeof(double));

    memcpy(ruleArray, mxGetPr(fmldata.Rule), fmldata.config.RULE_AMOUNT * fmldata.config.RULE_LENGTH * sizeof(double));

    // [Start] Debug printing got ruleArray matrix

//    cout << "Rules in array form is:" << endl;

//    for (int i = 0; i <fmldata.config.RULE_AMOUNT * fmldata.config.RULE_LENGTH; i++) {
//        cout << ruleArray[i] << " ";
//    }
//    cout << endl;
/*
    cout << "Rules in matrix form is:" << endl;
    for (int i = 0; i < fmldata.config.RULE_AMOUNT; i++) {
        for (int j = 0; j < fmldata.config.RULE_LENGTH; j++) {
            cout << ruleArray[j * fmldata.config.RULE_AMOUNT + i] << " ";
        }
        cout << endl;
    }
*/
//    cout << "Rules in matrix form is:" << endl;
    for (int i = 0; i < fmldata.config.RULE_AMOUNT; i++) {
        char newmess[100];
        for (int j = 0; j < fmldata.config.RULE_LENGTH; j++) {
            newmess[j]=ruleArray[j * fmldata.config.RULE_AMOUNT + i];
            //cout << ruleArray[j * fmldata.config.RULE_AMOUNT + i] << " ";
        }
        if (newmess[0]==1)
        {
            //cout << "GOMESS"<<endl;

            char * newmessage=new char[100];
            memcpy(newmessage,newmess,100);
            emit sendToBTtransmitter(newmessage);
        }
//        cout << endl;
    }
    // [End] Debug printing got ruleArray matrix

    //emit sendToConnector(ruleArray);
    clock_t dt=clock()-t;
    if (dt>maxt)
        maxt=dt;
    st=st+dt;
    if (clock()-mt>CLOCKS_PER_SEC)
    {
        mt=clock();
        QString temp;
        QString ToStatus="Using Matlab: Count=";
        temp.setNum(Time_count);
        ToStatus=ToStatus+temp;

        ToStatus=ToStatus+" ~time=";
        temp.setNum(st/Time_count);
        ToStatus=ToStatus+temp;

        ToStatus=ToStatus+" maxtime=";
        temp.setNum(maxt);
        ToStatus=ToStatus+temp;

        ToStatus=ToStatus+" ~fulltime=";
        temp.setNum(st);
        ToStatus=ToStatus+temp;

        st=0;
        maxt=0;
        Time_count=0;
        emit StatusMessage(ToStatus);
    }
    emit ForvardReciver();
}
