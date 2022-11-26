#ifndef PERCEPTRON_H
#define PERCEPTRON_H

typedef struct data *Data;
typedef struct model *Model;

//Building
Data new_Data(const char *fname);
Model new_Model(const Data data);

//Training
void fit_model(Model model, Data data);

//Scoring
void run_scoring_engine(const Model model);

#endif
