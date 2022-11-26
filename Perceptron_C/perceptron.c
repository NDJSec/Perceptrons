#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

struct shape {
	int number_of_examples;
	int number_of_features;
	int dimensions;
};

struct points {
	double xcoord;
	double ycoord;
	int target;
};

struct data {
	double **elements;
	int *targets;
	struct points data_points;
	struct shape data_shape;
};

struct model {
	double *weights;
	struct shape model_shape;
};

Data new_Data(const char *fname) {
	FILE *fp;

	if((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "load_data: can't open %s\n", fname);
		exit(1);
	}

	int number_of_example_lines = 0;
	char ch;
	while((ch = fgetc(fp)) != EOF) {
		if(ch == '\n') {
			number_of_example_lines++;
		}
	}

	Data data = (Data) malloc(sizeof(struct data));
	data->data_shape.number_of_examples = number_of_example_lines;
	data->data_shape.number_of_features = 2;
	data->elements = (double**) malloc(data->data_shape.number_of_features * sizeof(double*));

	for(int i = 0; i < data->data_shape.number_of_examples; i++) {
		data->elements[i] = malloc(data->data_shape.number_of_examples * sizeof(double));
	}

	data->targets = (int*) malloc(data->data_shape.number_of_examples * sizeof(int));

	rewind(fp);

	int i = 0;
	double target;
	while(fscanf(fp, "%lf %lf %lf", &(data->elements[0][i]), &(data->elements[1][i]), &target) != EOF) {
		data->targets[i] = (int)target;
		i++;
	}

	fclose(fp);
	fprintf(stdout, "load_data: loaded %d examples\n", i);

	return data;
}

Model new_Model(const Data data) {
	Model model = (Model) malloc(sizeof(Model));
	model->model_shape.dimensions = data->data_shape.number_of_features + 1;
	model->weights = (double*) malloc(model->model_shape.dimensions * sizeof(double));

	for(int i = 0; i < model->model_shape.dimensions; i++) {
		model->weights[i] = (double) rand() / RAND_MAX;
	}

	return model;
}

static void sgd(Model model, Data data) {
	model->weights[2] += data->data_points.target * data->data_points.xcoord;
	model->weights[1] += data->data_points.target * data->data_points.ycoord;
    model->weights[0] += data->data_points.target * 1;
}

static int predict(Model model, Data data) {
	double hypothesis = model->weights[2] * data->data_points.xcoord + model->weights[1] * data->data_points.ycoord + model->weights[0];
	return(hypothesis < 0) ? -1 : 1;
}

void fit_model(Model model, Data data) {
	double hypothesis;

	bool misclassified = true;
	while(misclassified) {
		misclassified = false;
		for(int i = 0; i < data->data_shape.number_of_examples; i++) {
			data->data_points.xcoord = data->elements[0][i];
			data->data_points.ycoord = data->elements[1][i];
			hypothesis = predict(model, data);
			if((hypothesis > 0 && data->data_points.target > 0) || (hypothesis < 0 && data->data_points.target < 0)) {
				continue;
			}
			sgd(model, data);
			misclassified = true;
		}
	}
}

void run_scoring_engine(const Model model) {
	Data data = (Data) malloc(sizeof(Data));

	printf("Enter x: \n");
	scanf("%lf", &(data->data_points.xcoord));

	printf("Enter y: \n");
	scanf("%lf", &(data->data_points.ycoord));

	printf("Prediction = %d\n", predict(model, data));
}
