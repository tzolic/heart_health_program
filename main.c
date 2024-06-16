/*
==========================================================================================================================
Name       : Hearth Health Program
Author     : tzolic
Description: A program that lets you calculate your BMI, take a blood pressure assessment, and calculate your ERICE score.
==========================================================================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>




/*-----------function prototypes-----------*/

char* inputHandler(char* prompt, char* error_prompt, int (*condition)(char* input));
int menuCondition(char* input);

void BMI(void);
int BMICondition1(char* input);
int BMICondition2(char* input);

void bloodPressure(void);
int systolicCondition(char* input);
int diastolicCondition(char* input);

void cardiacRisk(void);
int ageCondition(char* input);
int booleanCondition(char* input);
int diabeticCondition(char* input);
int cholesterolCondition(char* input);

double average(int* arr, int size);





int main(void){
  char* choice = inputHandler("1-BMI (body mass index calculation)\n2-Blood pressure assessment\n3-ERICE score assessment\n4-Exit\nEnter your choice:\n", "Input error! Please choose a number between 1 and 4:\n", menuCondition);
  if(strcmp("1",choice) == 0){
    BMI();
    puts("");
    main();
  }
  else if(strcmp("2",choice) == 0){
    bloodPressure();
    puts("");
    main();
  }
  else if(strcmp("3",choice) == 0){
    cardiacRisk();
    puts("");
    main();
  }
  else if(strcmp("4",choice) == 0){
    printf("\033[1;32m");
    printf("Thanks for using our hearth health program!");
    printf("\033[0m"); 
  }
  
  return 0;
}





void BMI(void){
  char* num1 = inputHandler("Enter your weight (between 20 and 500kg):\n", "Input error! Please enter your weight between 20 and 500kg:\n", BMICondition1);
  char* num2 = inputHandler("Enter your height (between 0.5 and 2.5m):\n", "Input error! Please enter your height between 0.5 and 2.5m:\n", BMICondition2);
  
  double weight = atof(num1);
  double height = atof(num2);

  double BMI_num = (weight / pow(height, 2));

  printf("\033[1;32m");
  printf("Your BMI is: %.1lf\n", BMI_num);

  if(BMI_num < 18.5){
    puts("Your BMI < 18.5: you are underweight.");
  }
  else if(BMI_num >= 18.5 && BMI_num <= 24.9){
    puts("Your BMI is between 18.5 and 24.9: you have an ideal weight.");
  }
  else if(BMI_num >= 25 && BMI_num <= 29.9){
    puts("Your BMI is between 25 and 29.9: you are overweight.");
  }
  else if(BMI_num >= 30){
    puts("Your BMI >= 30: you are obsese.");
  }
  printf("\033[0m");
}




void bloodPressure(void){
  char* num1 = inputHandler("Enter your systolic blood pressure (between 70 and 190mmHg, the ideal range is between 90 and 120mmHg):\n", "Input error! Please enter a systolic blood pressure between 70 and 190mmHg:\n", systolicCondition);
  char* num2 = inputHandler("Enter your diastolic blood pressure (between 40 and 100mmHg, the ideal range is between 60 and 80mmHg):\n", "Input error! Please enter a diastolic blood pressure between 40 and 100mmHg:\n", diastolicCondition);
  
  double systolic_reading = atof(num1);
  double diastolic_reading = atof(num2);
  
  printf("\033[1;32m");

  if((systolic_reading >= 70 && systolic_reading <= 90)&&(diastolic_reading >= 40 && diastolic_reading <= 60)){
    puts("Your blood pressure is low: your heart isn't pumping as forcefully as it should.");
  }
  else if(((systolic_reading >= 70 && systolic_reading <= 120) && (diastolic_reading >= 60 && diastolic_reading <= 80))||((systolic_reading >= 90 && systolic_reading <= 120) && (diastolic_reading >= 40 && diastolic_reading <= 80))){
    puts("Your blood pressure is ideal: you have a healthy balance of blood flow in your arteries.");
  }
  else if(((systolic_reading >= 70 && systolic_reading <= 140)&&(diastolic_reading >= 80 && diastolic_reading <= 90))||((systolic_reading >= 120 && systolic_reading <= 140)&&(diastolic_reading >= 40 && diastolic_reading <= 90))){
    puts("Your blood pressure is pre-high: you are at risk of developing high blood pressure if not managed properly.");
  }
  else if(((systolic_reading >= 70 && systolic_reading <= 190)&&(diastolic_reading >= 90 && diastolic_reading <= 100))||((systolic_reading >= 140 && systolic_reading <= 190)&&(diastolic_reading >= 40 && diastolic_reading <= 100))){
    puts("Your blood pressure is high: you are at risk of heart disease, stroke, and other cardiovascular problems.");
  }

  printf("\033[0m");
}




void cardiacRisk(void){
  puts("Lets calculate your ERICE risk score! (assuming that you are not undergoing antihypertensive treatment)\nAn ERICE score is the likelihood in percentage that you will experience heart-related issues within the next 10 years (it's a bit depressing but better be safe than surprised).\n");

  /*----------tables written in 2d arrays----------*/

  int men_ERICE_data[24][16] = 
  {
  {56,57,58,55,66,67,69,65,46,47,48,45,56,57,58,55}, //1
  {54,54,56,52,64,65,67,63,44,45,46,43,54,54,56,52}, //2
  {51,51,53,49,61,62,64,60,41,42,44,40,51,51,53,49}, //3
  {38,38,40,36,47,47,49,45,30,30,32,30,38,38,40,36}, //4
  {35,35,37,34,43,44,45,42,27,28,29,27,35,35,37,34}, //5
  {33,33,35,32,41,42,43,40,26,26,28,25,33,33,35,32}, //6
  {31,31,33,30,39,39,41,37,24,25,26,23,31,31,33,30}, //7
  {22,22,23,21,28,28,29,27,17,17,18,16,22,22,23,21}, //8
  {24,24,25,23,30,30,32,32,18,19,19,18,24,24,25,23}, //9
  {22,23,24,22,28,29,30,30,17,18,18,17,22,23,24,22}, //10
  {21,21,22,20,27,27,28,26,16,16,17,15,21,21,22,20}, //11
  {14,15,15,15,19,19,19,18,11,11,12,11,14,15,15,15}, //12
  {12,12,13,12,16,16,17,15,9,10,10,10,12,12,13,12}, //13
  {12,12,12,11,15,15,16,16,9,9,9,9,12,12,12,11}, //14
  {11,11,11,10,14,14,14,13,8,8,9,8,11,11,11,10}, //15
  {7,7,8,7,9,10,10,9,6,6,6,5,7,7,8,7}, //16
  {5,5,5,5,6,6,6,6,3,3,4,3,4,5,5,5}, //17
  {4,4,5,5,6,6,6,5,3,3,3,3,4,4,5,5}, //18
  {4,4,4,4,5,5,5,5,3,3,3,3,4,4,4,4}, //19
  {3,3,3,3,3,4,4,3,2,2,2,2,3,3,3,3}, //20
  {2,2,3,2,3,3,3,3,2,2,2,2,2,2,3,2}, //21
  {2,2,2,2,3,3,3,3,2,2,2,2,2,2,2,2}, //22
  {2,2,2,2,3,3,3,3,2,2,2,2,2,2,2,2}, //23
  {1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1} //24
  };

  int women_ERICE_data[20][16] =
  {
  {70,71,69,63,84,84,83,77,54,55,53,46,69,69,68,61}, //1
  {50,50,49,52,64,65,64,56,36,36,35,30,48,49,48,41}, //2
  {56,57,55,48,71,72,70,63,41,42,40,34,55,55,54,47}, //3
  {54,54,53,46,69,69,68,60,39,40,38,33,53,53,52,45}, //4
  {39,39,38,33,53,53,52,34,27,28,27,22,38,38,37,32}, //5
  {24,25,24,20,34,35,34,30,16,17,16,15,24,24,23,20}, //6
  {29,29,28,24,40,40,39,33,19,19,19,16,28,28,27,23}, //7
  {27,27,27,22,38,38,37,32,18,19,18,15,26,27,26,22}, //8
  {21,21,21,20,29,29,29,25,14,14,14,11,20,21,20,20}, //9
  {13,13,12,10,18,19,18,15,8,8,8,7,12,12,12,10}, //10
  {14,14,14,12,19,19,19,18,9,9,9,8,14,14,14,12}, //11
  {14,14,14,11,19,19,19,17,9,9,9,7,14,14,13,11}, //12
  {12,12,12,10,18,18,17,15,8,8,8,6,12,12,11,10}, //13
  {7,7,7,6,10,10,10,10,5,5,5,5,7,7,7,5}, //14
  {8,8,8,7,12,12,12,10,5,6,5,5,8,8,8,6}, //15
  {8,8,8,6,12,12,11,10,5,5,5,5,8,8,7,6}, //16
  {2,2,1,1,2,2,2,2,1,1,1,1,1,1,1,1}, //17
  {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1}, //18
  {1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1}, //19
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} //20
  };

  /*----------values initialization----------*/

  //row values
  int age;
  double systolic; //systolic blood pressure (in mmHg)

  //column values
  int gender; //1 for male, 0 for female
  int smoker; //1 for smoker, 0 for non-smoker
  int diabetic; //1 if diabetic, 0 if non-diabetic
  double cholesterol; //total cholesterol level (in mmol/L)

  //prompts
  char* num1 = inputHandler("Enter your age (between 30 and 130years):\n", "Input error! Please enter an age between 30 and 130years:\n", ageCondition);
  char* num2 = inputHandler("Enter your systolic blood pressure (between 70 and 190mmHg, the ideal range is between 90 and 120mmHg):\n", "Input error! Please enter a systolic blood pressure between 70 and 190mmHg:\n", systolicCondition);
  char* num3 = inputHandler("Enter 0 if you are a woman and 1 if you are a man:\n", "Input error! Please enter 1 or 0:\n", booleanCondition);
  char* num4 = inputHandler("Enter 0 if you are a non-smoker and 1 is you are a smoker:\n", "Input error! Please enter 0 or 1:\n", booleanCondition);
  char* num5 = inputHandler("Enter 0 if you are non-diabetic and 1 if you are diabetic:\n", "Input error! Please enter 0 or 1:\n", booleanCondition);
  char* num6 = inputHandler("Enter your cholesterol level (between 3 and 10mmol/L, the ideal range is <= 5.2mmol/L):\n", "Input error! Please enter a choresterol level between 3 and 10mmol/L:\n", cholesterolCondition);

  age = atoi(num1);
  systolic = atof(num2);
  gender = atoi(num3);
  smoker = atoi(num4);
  diabetic = atoi(num5);
  cholesterol = atof(num6);
  
  //row & column indexes initialization
  int row_index = 0;
  int column_index = 0;

  /*----------men data----------*/

  //men row movement
  if(gender == 1)
  {
    //age movement
    if(age >= 70 && age <= 79){
      row_index += 4;
    }
    else if(age >= 60 && age <= 69){
      row_index += 8;
    }
    else if(age >= 50 && age <= 59){
      row_index += 12;
    }
    else if(age >= 40 && age <= 49){
      row_index += 16;
    }
    else if(age >= 30 && age <= 39){
      row_index += 20;
    }
    //systolic movement
    if(systolic >= 160 && systolic <= 179){
      row_index += 1;
    }
    else if(systolic >= 140 && systolic <= 159){
      row_index += 2;
    }
    else if(systolic <= 139){
      row_index += 3;
    }
  }

  //men column movement
  if(gender == 1){
    //smoker movement
    if(smoker == 1){
      column_index += 4;
    }
    //diabetic  movement
    if(diabetic == 0){
      column_index += 8;
    }
    //cholesterol movement
    if(cholesterol >= 5.2 && cholesterol <= 6.4){
      column_index += 1;
    }
    else if(cholesterol >= 6.5 && cholesterol <= 7.7){
      column_index += 2;
    }
    else if(cholesterol >= 7.8){
      column_index += 3;
    }
  }

  /*----------women data----------*/

  //women row movement
  if(gender == 0)
  {
    //age movement
    if(age >= 70 && age <= 79){
      row_index += 4;
    }
    else if(age >= 60 && age <= 69){
      row_index += 8;
    }
    else if(age >= 50 && age <= 59){
      row_index += 12;
    }
    else if(age >= 30 && age <= 49){
      row_index += 16;
    }
    //systolic movement
    if(systolic >= 160 && systolic <= 179){
      row_index += 1;
    }
    else if(systolic >= 140 && systolic <= 159){
      row_index += 2;
    }
    else if(systolic <= 139){
      row_index += 3;
    }
  }

  //women column movement
  if(gender == 0){
    //smoker movement
    if(smoker == 1){
      column_index += 4;
    }
    //diabetic  movement
    if(diabetic == 0){
      column_index += 8;
    }
    //cholesterol movement
    if(cholesterol >= 5.2 && cholesterol <= 6.4){
      column_index += 1;
    }
    else if(cholesterol >= 6.5 && cholesterol <= 7.7){
      column_index += 2;
    }
    else if(cholesterol >= 7.8){
      column_index += 3;
    }
  }

  if(gender == 1){
    printf("\033[1;32m");
    printf("Your ERICE cardiovascular score is: %d%%.\nIt means that in the next 10 years, the risk of a dangerous cardiac event is %d%%.\n", men_ERICE_data[row_index][column_index], men_ERICE_data[row_index][column_index]);
    printf("\033[0m");  
  }
  else if(gender == 0){
    printf("\033[1;32m");
    printf("Your ERICE cardiovascular score is: %d%%\nIt means that in the next 10 years, the risk of a dangerous cardiac event is %d%%.\n", women_ERICE_data[row_index][column_index], women_ERICE_data[row_index][column_index]);
    printf("\033[0m"); 
  }
}




char* inputHandler(char* prompt, char* error_prompt, int (*condition)(char* input)){
  //choose initial buffer size
  size_t buffer_size = 300;

  //allocate dynamically memory input buffer
  char* input = (char*)malloc(buffer_size * sizeof(char));
  if (input == NULL){
      fprintf(stderr, "Memory allocation failed!");
      exit(1);
  }

  //display prompt
  printf("%s", prompt);
  fflush(stdout);

  //read input in stdin
  fgets(input, buffer_size, stdin);
  input[strlen(input) - 1] = '\0';

  //handle length error
  while((strlen(input) + 2) >= buffer_size){
    //clear buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\033[1;31m");
    //length error prompt
    printf("Length error! Input exceeds maximum input limit. Please enter a shorter input:\n");
    fflush(stdout);
    printf("\033[0m");

    fgets(input, buffer_size, stdin);
    input[strlen(input) - 1] = '\0';
  }

  //handle condition error
  while(condition(input) == 0){
    printf("\033[1;31m");
    //error prompt
    printf("%s", error_prompt);
    fflush(stdout);
    printf("\033[0m");
    
    fgets(input, buffer_size, stdin);
    input[strlen(input) - 1] = '\0';

    //handle length error again inside condition error
    while((strlen(input) + 2) >= buffer_size){
      int c;
      while ((c = getchar()) != '\n' && c != EOF);

      printf("\033[1;31m");
      printf("Length error! Input exceeds maximum input limit. Please enter a shorter input:\n");
      fflush(stdout);
      printf("\033[0m");

      fgets(input, buffer_size, stdin);
      input[strlen(input) - 1] = '\0';
    }
  }
  return input;
}




/*----------condition functions----------*/

int menuCondition(char* input)
{
  if(strcmp("1",input) == 0 || strcmp("2",input) == 0 || strcmp("3",input) == 0 || strcmp("4",input) == 0){
    return 1;
  }
  return 0;
}

int BMICondition1(char* input)
{
  int num = atoi(input);
  if(num >= 20 && num <= 500){
    return 1;
  }
  return 0;
}

int BMICondition2(char* input)
{
  double num = atof(input);
  if(num >= 0.5 && num <= 2.5){
    return 1;
  }
  return 0;
}

int systolicCondition(char* input)
{
  double num = atof(input);
  if(num >= 70 && num <= 190){
    return 1;
  }
  return 0;
}

int diastolicCondition(char* input)
{
  double num = atof(input);
  if(num >= 40 && num <= 100){
    return 1;
  }
  return 0;
}

int ageCondition(char* input)
{
  int num = atoi(input);
  if(num >= 30 && num <= 130){
    return 1;
  }
  return 0;
}


int booleanCondition(char* input)
{
  int num = atoi(input);
  if((num == 1) || (num == 0 && strcmp("0",input) == 0)){
    return 1;
  }
  return 0;
}

int cholesterolCondition(char* input)
{
  double num = atof(input);
  if(num >= 3 && num <= 10){
    return 1;
  }
  return 0;
}





double average(int* arr, int size){
  double sum = 0;
  for(int i = 0; i < size; i++){
    sum += arr[i];
  }
  return (sum / size); 
}