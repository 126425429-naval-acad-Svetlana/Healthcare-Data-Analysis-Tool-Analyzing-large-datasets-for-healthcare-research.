#include <stdio.h> 
#define MAX 1000 
// Структура за съхранение на данни за пациенти 
typedef struct 
{ 
int id; //уникален идентификатор на пациента
int age;  //възраст на пациента
char gender; //пол на пациентите ('M' или 'F')
int bp;  //кръвно налягане
int cholesterol; //ниво на холестерол
} Patient; 
// Деклариране на функциите 
int load_data(Patient patients[]); 
// Изчислява и извежда обща статистика за всички пациенти
// (например общ брой, средна възраст, среден риск и др.)
void overall_stats(Patient patients[], int count); 
// Изчислява и извежда статистика за пациентите по пол
// (например брой мъже и жени, процентно разпределение и др.)
void gender_stats(Patient patients[], int count); 
// Изчислява и извежда статистика според рисковите групи
// (например нисък, среден и висок риск)
void risk_stats(Patient patients[], int count); 
//главна функция на програмата
//Управлява изпълнението на програмата и извиква останалите функции
int main(void) 
{ 
Patient patients[MAX]; //Масив за съхранение на данните за пациентите
int count = load_data(patients); //зареждане ан данните от файла 
if (count == 0) 
{ 
        printf("No data available.\n"); 
        return 1; 
    } 
    printf("\nHealthcare Data Analysis Tool\n"); 
    printf("=============================\n"); 
    //извежда обща статистика
    overall_stats(patients, count); 
    //извежда статистика за пола
    gender_stats(patients, count); 
    //анализ на пациенти с висок риск
    risk_stats(patients, count); 
    
    return 0; 
} 
/* 
 * Функция за зареждане на данни за пациенти от CSV файл.
 * Чете файла "patients.csv", пропуска заглавния ред
 * и попълва масива с пациенти.
 * Връща броя успешно заредени записи.
 */ 
int load_data(Patient patients[]) 
{ 
    FILE *file = fopen("patients.csv", "r"); 
    //проверка дали файлът е отворен успешно
    if (file == NULL) 
    { 
        printf("Error opening file.\n"); 
        return 0; 
    } 
    // пропускане на първия ред (заглавията на контролите) 
    fscanf(file, "%*[^\n]\n"); 
  
    int i = 0; 
    // четене на данните ред по ред от файла
    while (fscanf(file, "%d,%d,%c,%d,%d", 
                  &patients[i].id, 
                  &patients[i].age, 
                  &patients[i].gender, 
                  &patients[i].bp, 
                  &patients[i].cholesterol) == 5) 
    { 
        i++; 
        // проверка дали не е достигнат максималния размер на масива
        if (i >= MAX) 
        { 
            break; 
        } 
    } 
    
    //затваряне на файла
    fclose(file); 
    //връщане на броя заредени пациенти
    return i; 
} 

// Oфункция за обща статистика
//изчислява общия брой пациенти и средната им възраст
void overall_stats(Patient patients[], int count) 
{ 
    float age_sum = 0; 
    
    //сумиране на възрастите на всички пациенти
    for (int i = 0; i < count; i++) 
    { 
        age_sum += patients[i].age; 
    } 
    printf("\n--- Overall Statistics ---\n"); 
    printf("Total patients: %d\n", count); 
    printf("Average age: %.2f\n", age_sum / count); 
} 
// функция за статистика по пол 
// преброява мъже и жени и изчислява средната възраст за всеки пол
void gender_stats(Patient patients[], int count) 
{ 
    int males = 0, females = 0; 
    float male_age = 0, female_age = 0; 
    //обхождане на всички пациенти
    for (int i = 0; i < count; i++) 
    { 
        if (patients[i].gender == 'M') 
        { 
            males++; 
            male_age += patients[i].age; 
        } 
        else if (patients[i].gender == 'F') 
        { 
            females++; 
            female_age += patients[i].age; 
        } 
    } 
    printf("\n--- Gender Statistics ---\n"); 
    // извеждане на резултатите за мъжете
    if (males > 0) 
        printf("Males: %d | Avg age: %.2f\n", males, male_age / males); 
    //извеждане на данни за жените
    if (females > 0) 
        printf("Females: %d | Avg age: %.2f\n", females, female_age / females); 
} 
/* 
 * Функция за анализ на пациенти с висок риск.
 * Открива пациенти с високо кръвно налягане
 * или висок холестерол и ги извежда на екрана.
 */
void risk_stats(Patient patients[], int count) 
{ 
    int risk = 0; 
    printf("\n--- High Risk Patients ---\n");
    //проверка на всеки пациент за рискови стойности 
    for (int i = 0; i < count; i++) 
    { 
        if (patients[i].bp > 140 || patients[i].cholesterol > 240) 
        { 
            printf("ID %d | BP %d | Chol %d\n", 
                   patients[i].id, 
                   patients[i].bp, 
                   patients[i].cholesterol); 
            risk++; 
        } 
    } 
    //извеждане на общия брой рискови пациенти 
    printf("Total high-risk patients: %d\n", risk); 
}