#include "mnist.h"
#include "data.h"
#include <math.h>
#include <stdio.h>

#define INPUTINDEX 784
#define OUTPUTINDEX 10

#define SECONDNN 50
#define THURDNN 100

#define NEIPIA 2.71828182846

float sigmoid(float x);
float step_function(float x);
char deeplearning();

float sigmoid(float x)
{
  return 1 / (1 + (pow(NEIPIA, -x)));
}
float step_function(float x)
{
  if (x>0.0f) return 1.0f;
  else return 0.0f;
}
float relu(float x)
{
  if (x>0) return x;
  else return 0.0f;
}
void softmax(float x[])
{
  float sum = 0.0f;
  for(int i=0;i<OUTPUTINDEX;i++) x[i] = pow(NEIPIA, x[i]);
  for(int i=0;i<OUTPUTINDEX;i++) sum += x[i];
  for(int i=0;i<OUTPUTINDEX;i++) x[i] /= sum;
}
void network(float x[])
{
  float data1[SECONDNN];
  float data2[THURDNN];
  float data3[OUTPUTINDEX];
  for(int j=0;j<SECONDNN;j++){
    for(int k=0;k<INPUTINDEX;k++){
      data1[j] += x[k] * W1[k][j];
    }
    data1[j] += b1[j];
    data1[j] = sigmoid(data1[j]);
  }
  for(int j=0;j<THURDNN;j++){
    for(int k=0;k<SECONDNN;k++){
      data2[j] += data1[k] * W2[k][j];
    }
    data2[j] += b2[j];
    data2[j] = sigmoid(data2[j]);
  }
  for(int j=0;j<OUTPUTINDEX;j++){
    for(int k=0;k<THURDNN;k++){
      data3[j] += data2[k] * W3[k][j];
    }
    data3[j] += b3[j];
    x[j] = data3[j];
  }
}

int argmax(float x[])
{
  float tmp = x[0];
  int max=0;
  for(int i=1;i<OUTPUTINDEX;i++){
    if(x[i]>tmp){
      tmp = x[i];
      max = i;
    }
  }
  return max;
}
char deeplearning()
{
  float a[INPUTINDEX]; // 入力データ
  for(int i=0;i<784;i++){
      a[i] = dataset[i];
  }
  char num[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  network(a);
  softmax(a);
  printf("Hello\n");
  printf("%f\n", a[7]);
  return num[argmax(a)];
  //for (int i=0;i<OUTPUTINDEX;i++) printf("%f ", a[i]);
  //printf("\n");
}
