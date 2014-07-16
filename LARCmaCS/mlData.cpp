#include "mlData.h"

MlData::MlData(RCConfig conf)
{

//    memset(&config, 0, sizeof(RCConfig));
//    memcpy(&config, &conf, sizeof(RCConfig));

      config = conf;

//    Rules_length = mxCreateDoubleMatrix(1, 1, mxREAL);
//    Rules_count  = mxCreateDoubleMatrix(1, 1, mxREAL);
//    Ball         = mxCreateDoubleMatrix(1, 3, mxREAL);
//    Blue         = mxCreateDoubleMatrix(12, 4, mxREAL);
//    Yellow       = mxCreateDoubleMatrix(12, 4, mxREAL);
//    Rule         = mxCreateDoubleMatrix(config.RULE_LENGTH, config.RULE_AMOUNT, mxREAL);
//    Back_Params  = mxCreateDoubleMatrix(config.BACK_LENGTH, config.BACK_AMOUNT, mxREAL);
//    Back_Amount  = mxCreateDoubleMatrix(1, 1, mxREAL);
//    Back_Length  = mxCreateDoubleMatrix(1, 1, mxREAL);

}

MlData::MlData(const MlData &dat)
{
    memset(&config, 0, sizeof(RCConfig));
    memcpy(&config, &dat.config, sizeof(RCConfig));

//    Rules_length = mxCreateDoubleMatrix(1, 1, mxREAL);
//    memcpy(Rules_length, &dat.Rules_length, sizeof(Rules_length));
//    Rules_count  = mxCreateDoubleMatrix(1, 1, mxREAL);
//    memcpy(Rules_count, &dat.Rules_count, sizeof(Rules_count));
//    Ball         = mxCreateDoubleMatrix(1, 3, mxREAL);
//    memcpy(Ball, &dat.Ball, sizeof(Ball));
//    Blue         = mxCreateDoubleMatrix(12, 4, mxREAL);
//    memcpy(Blue, &dat.Blue, sizeof(Blue));
//    Yellow       = mxCreateDoubleMatrix(12, 4, mxREAL);
//    memcpy(Yellow, &dat.Yellow, sizeof(Yellow));
//    Rule         = mxCreateDoubleMatrix(config.RULE_LENGTH, config.RULE_AMOUNT, mxREAL);
//    memcpy(Rule, &dat.Rule, sizeof(Rule));
//    Back_Params  = mxCreateDoubleMatrix(config.BACK_LENGTH, config.BACK_AMOUNT, mxREAL);
//    memcpy(Back_Params, &dat.Back_Params, sizeof(Back_Params));
//    Back_Amount  = mxCreateDoubleMatrix(1, 1, mxREAL);
//    memcpy(Back_Amount, &dat.Back_Amount, sizeof(Back_Amount));
//    Back_Length  = mxCreateDoubleMatrix(1, 1, mxREAL);
//    memcpy(Back_Length, &dat.Back_Length, sizeof(Back_Length));

}
