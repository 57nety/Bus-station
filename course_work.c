#include <stdio.h>
#include <string.h>

#define SIZE 256

// список рейсов
typedef struct {

    char    flight_number[SIZE], // номер рейса
            destination[SIZE], // пункт назначения
            departure_date[SIZE], // дата отправления
            departure_time[SIZE], // время отправления
            total_number_of_seats[SIZE], // общее число пассажирских сидений
            ticket_price[SIZE]; // цена билета

    int     number_string;

} flight_list; // список рейсов

// максимальные длины позиций рейсов
typedef struct {

    int     MAX_len_number,
            MAX_flight_number,
            MAX_destination,
            MAX_departure_date,
            MAX_departure_time,
            MAX_total_number_of_seats,
            MAX_ticket_price;

} maximum_lengths_of_flight_positions;

// введённый запрос
typedef struct{

    char    flight_number[SIZE],
            destination[SIZE],
            departure_date[SIZE],
            departure_time[SIZE],
            total_number_of_seats[SIZE],
            ticket_price[SIZE];

} enter_request;

    

// создание нового списка рейсов
int create_a_new_flight_list(flight_list list);
// заполнение позиций рейса
int input(int number_of_flights,flight_list list);
// защита от ввода букв
int letter_entry_protection(char string[]);

// редактирование старого списка
int edit_existing_flight_list(int number_of_flights,flight_list list, maximum_lengths_of_flight_positions *maximum_lengths);

// изменить определенное поле
int change_a_specific_field(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths);
// замена информации
void replacement_of_information(char string[], int position);

// вывод списка рейсов
int output(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths);
// расстояние между полями
void distance_between_fields(char string[], int *max);
// заполнение структуры максимальных значений полей
int maximum_field_length(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths);
// выявление максимального значения
void identification_of_the_maximum_value(char string[],int *max);

// удалить определённый рейс
int delete_specific_flight(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths);

// добавить один или несколько рейсов
void add_one_or_more_flights(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths);
// добавление рейсов
int add_flights(int enter_number_flights,flight_list list);

// вывод имеющегося списка рейсов
void display_of_available_flights(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths);

// вывод рейсов по запросу
void search_for_a_suitable_flight(int number_of_flights, flight_list list, maximum_lengths_of_flight_positions *maximum_lengths,enter_request *enter);
// формирование запроса на поиск
void output_on_request(int number_of_flights, flight_list list, maximum_lengths_of_flight_positions *maximum_lengths,enter_request *enter);
// вывод найденных по запросу рейсов
int output_flights(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths, int f[]);
// поиск повторяющихся позиций
int search_for_similar_positions(int a[]);
// поиск рейсов по запросу
int search_for_flights_on_request(int number_of_flights, flight_list list, maximum_lengths_of_flight_positions *maximum_lengths,enter_request *enter);
// ввод запроса
void request_input(int a[],int number_of_flights, flight_list list, maximum_lengths_of_flight_positions *maximum_lengths,enter_request *enter);
// чистка позиций ввода запроса
void cleaning_input_items(enter_request *enter);
// печать номера рейса в зависимости от колличества цифр в числе
void print_line_number(int number, int max);

int main (void)
{
    int answer = 0, // ответ пользователя
        number_of_flights = 0, // число рейсов в базе данных
        flag = 0; // флаг

    flight_list list;
    maximum_lengths_of_flight_positions maximum_lengths;
    enter_request enter;

    flag = 0;
    FILE *fptr;
    fptr = fopen("flight_schedule.txt","r");
    if( fptr == NULL && flag == 1 )
    {
        printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
        fclose(fptr);
        return -1;
    }
    else
    {
        rewind(fptr);
        number_of_flights = 0;
        // проверка базы данных на наличие в ней рейсов
        while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF )
            number_of_flights++;
        fclose(fptr);
    }
    if( fptr == NULL && flag == 0 )
    {
        fclose(fptr);
        fptr = fopen("flight_schedule.txt","w");
        fclose(fptr);
        number_of_flights = 0;
        flag = 1;
    }
	

    do{
        printf("\r\n ***************** ");
        printf("\r\n *** Main menu *** ");
        printf("\r\n ***************** ");
        printf("\r\n 1. Create a new flight list \r\n 2. Edit existing flight list \r\n 3. Display of available flights \r\n 4. Search for a suitable flight \r\n 5. Exit from the program \r\n");
        printf("\r\n Indicate the number of what you would like to do (1,2,3,4,5): ");
        scanf("%d",&answer);
        fflush(stdin);
        if( answer == 1 )
            number_of_flights = create_a_new_flight_list(list);
        if( answer == 2 )
            if( number_of_flights > 0 )
                number_of_flights = edit_existing_flight_list(number_of_flights,list,&maximum_lengths);
            else
                printf("\r\n *** The list of flights is empty! *** \r\n");
        if( answer == 3 )
            if( number_of_flights > 0 )
                display_of_available_flights(list,&maximum_lengths);
            else
                printf("\r\n *** The list of flights is empty! *** \r\n");
        if( answer == 4 )
            if( number_of_flights > 0 )
                search_for_a_suitable_flight(number_of_flights,list,&maximum_lengths,&enter);
            else
                printf("\r\n *** The list of flights is empty! *** \r\n");
    }while( answer != 5 );

    printf("\r\n Thanks for using the program!Please click ENTER.");
    fflush(stdin);
    getchar();      

    return 0;
}
// вывод рейсов по запросу
void search_for_a_suitable_flight(int number_of_flights, flight_list list, maximum_lengths_of_flight_positions *maximum_lengths,enter_request *enter)
{
    int answer = 0; // ответ пользователя
    do{
        do{
            printf("\r\n ************************************ ");
            printf("\r\n *** Search for a suitable flight *** ");
            printf("\r\n ************************************ \r\n");
            printf("\r\n 1. Enter a search query for suitable flights \r\n 2. Go back to the *** Main menu *** \r\n");
            printf("\r\n Indicate the number of what you would like to do (1,2): ");
            scanf("%d",&answer);
            fflush(stdin);
        }while( answer != 1 && answer != 2 );
        if( answer == 1 )
        {
            output(list,maximum_lengths);
            output_on_request(number_of_flights,list,maximum_lengths,enter);
        }
    }while( answer != 2 );
}
// формирование запроса на поиск
void output_on_request(int number_of_flights, flight_list list, maximum_lengths_of_flight_positions *maximum_lengths,enter_request *enter)
{
    int flag = 0, // флаг
        ok = 0, // флаг
        a[6] = {}, // отмеченные поля для поиска
        i = 0; // индекс

    ok = 0;
    i = 0;
    do{
        do{
            do{
                printf("\r\n Enter the number of the position for which you want to search, and click ENTER (1,2,3,4,5,6): ");
                scanf("%d",&a[i]);
            }while( a[i] != 1 && a[i] != 2 && a[i] != 3 && a[i] != 4 && a[i] != 5 && a[i] != 6 );
            if( search_for_similar_positions(a) )
            {
                printf("\r\n *** You have already indicated the number of this position! Try again! *** \r\n");
                flag = 1;
            }
            else
                flag = 0;
        }while( flag );
        i++;
        if( i == 6 )
            ok = 1;
        printf("\r\n if you want to specify one more position, then press enter, otherwise enter the symbol '#': ");
        fflush(stdin);
    }while( getchar() != '#' && i < 6 );

    if( ok )
        printf("\r\n *** You have indicated all possible positions *** \r\n");

    request_input(a,number_of_flights,list,maximum_lengths,enter);
}
// чистка позиций ввода запроса
void cleaning_input_items(enter_request *enter)
{
    for( int i = 0; i < SIZE; i++ )
    {
        enter->flight_number[i] = 0;
        enter->destination[i] = 0;
        enter->departure_date[i] = 0;
        enter->departure_time[i] = 0;
        enter->total_number_of_seats[i] = 0;
        enter->ticket_price[i] = 0;
    }
}
// ввод запроса
void request_input(int a[],int number_of_flights, flight_list list, maximum_lengths_of_flight_positions *maximum_lengths,enter_request *enter)
{
    int flag = 0;
    cleaning_input_items(enter);
    // согласно указанным полям поиска вводится информация для поиска
    for( int i = 0; i < 6; i++ )
        if( a[i] != 0 )
            switch(a[i])
            {
                case 1:
                    do{
                        printf("\r\n Enter the flight number you are looking for: ");
                        scanf("%s",enter->flight_number);
                        fflush(stdin);
                    }while( letter_entry_protection(list.flight_number) );
                    break;
                case 2:
                    printf("\r\n Enter the city whose flight you are looking for: ");
                    scanf("%s",enter->destination);
                    fflush(stdin);
                    break;
                case 3:
                    do{
                        printf("\r\n Enter departure date (dd.mm.yyyy): ");
                        scanf("%s",enter->departure_date);
                        fflush(stdin);
                        if( strlen(enter->departure_date) != 10 )
                            flag = 1;
                        else
                            if( enter->departure_date[2] != '.' || enter->departure_date[5] != '.' )
                                flag = 1;
                            else
                                flag = 0;
                    }while( letter_entry_protection(enter->departure_date) || flag == 1 );
                    break;
                case 4:
                    do{
                        printf("\r\n Enter the time after which you do not want to go: ");
                        scanf("%s",enter->departure_time);
                        fflush(stdin);
                    }while( letter_entry_protection(enter->departure_time) );
                    break;
                case 5:
                    do{
                        printf("\r\n Enter the minimum required number of seats on the bus: ");
                        scanf("%s",enter->total_number_of_seats);
                        fflush(stdin);
                    }while( letter_entry_protection(enter->total_number_of_seats) );
                    break;
                case 6:
                    do{
                        printf("\r\n Enter the maximum allowable price for your flight: ");
                        scanf("%s",enter->ticket_price);
                        fflush(stdin);
                    }while( letter_entry_protection(enter->ticket_price) );
                    break;
            }

    search_for_flights_on_request(number_of_flights,list,maximum_lengths,enter);

}
// поиск рейсов по запросу
int search_for_flights_on_request(int number_of_flights, flight_list list, maximum_lengths_of_flight_positions *maximum_lengths,enter_request *enter)
{
    int f[1000] = {}, // массив флажков на 1000 рейсов
        k = 0,
        i = 0; // индекс
    char s1[SIZE] = {}, s2[SIZE] = {};
    FILE *fptr;
    fptr = fopen("flight_schedule.txt","rt");
    if( fptr == NULL )
    {
        printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
        fclose(fptr);
        return -1;
    }
    rewind(fptr);
    i = 0;
    // фильтрация всех рейсов, по введённому запросу
    while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF )
    {
        if( strlen(enter->flight_number) != 0 && f[i] == 0 )
        {
                if( strcmp(enter->flight_number,list.flight_number) == 0 )
                    f[i] = 0;
                else
                    f[i] = 1;
        }
        if( strlen(enter->destination) != 0 && f[i] == 0 )
        {
                if( strcmp(enter->destination,list.destination) == 0 )
                    f[i] = 0;
                else
                    f[i] = 1;
        }
        if( strlen(enter->departure_date) != 0 && f[i] == 0 )
        {   
            if( strlen(list.departure_date) > 5 )

                k = 0;
                for(int j = 6; j < 10; j++ )
                {
                    s1[k] = enter->departure_date[j];
                    k++;
                }
                for(int j = 3; j < 5; j++ )
                {
                    s1[k] = enter->departure_date[j];
                    k++;
                }
                for(int j = 0; j < 2; j++ )
                {
                    s1[k] = enter->departure_date[j];
                    k++;
                }
                s1[k] = '\0';
                k = 0;
                for(int j = 6; j < 10; j++ )
                {
                    s2[k] = list.departure_date[j];
                    k++;
                }
                for(int j = 3; j < 5; j++ )
                {
                    s2[k] = list.departure_date[j];
                    k++;
                }
                for(int j = 0; j < 2; j++ )
                {
                    s2[k] = list.departure_date[j];
                    k++;
                }
                s2[k] = '\0';

                if( strcmp(s1,s2) >= 0 )
                    f[i] = 0;
                else
                    f[i] = 1;
        }
        if( strlen(enter->departure_time) != 0 && f[i] == 0 )
        {
                if( strcmp(enter->departure_time,list.departure_time) >= 0 )
                    f[i] = 0;
                else
                    f[i] = 1;
        }
        if( strlen(enter->total_number_of_seats) != 0 && f[i] == 0 )
        {
                if( strcmp(enter->total_number_of_seats,list.total_number_of_seats) <= 0 )
                    f[i] = 0;
                else
                    f[i] = 1;
        }
        if( strlen(enter->ticket_price) != 0 && f[i] == 0 )
        {
                if( strcmp(enter->ticket_price,list.ticket_price) >= 0 )
                    f[i] = 0;
                else
                    f[i] = 1;
        }
        i++;
    }
    fclose(fptr);

    output_flights(list,maximum_lengths,f);

}
// поиск повторяющихся позиций
int search_for_similar_positions(int a[])
{
    // проверка того, что указанные пользователем поля для поиска не повторяются
    int ok = 0;
    for( int i = 0; i < 6; i++ )
        if( a[i] != 0 )
            for( int j = i+1; j < 6; j++ )
                if( a[i] == a[j] )
                    ok = 1;
    return ok;
}
// вывод найденных по запросу рейсов
int output_flights(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths, int f[])
{
    int star = 0, // звезда, переменная показывающая количество печатаемыз звёзд
        flag = 0, // флаг
        max = 0, // максимальная длинна номера строки
        i = 0; // индекс
    char *sptr; // указатель для передачи  строк в функцию
    FILE *fptr;
    maximum_field_length(list,maximum_lengths);
    star = maximum_lengths->MAX_len_number + maximum_lengths->MAX_flight_number + maximum_lengths->MAX_destination + maximum_lengths->MAX_departure_date + maximum_lengths->MAX_departure_time + maximum_lengths->MAX_total_number_of_seats + maximum_lengths->MAX_ticket_price;
    star += 20;
    max = maximum_lengths->MAX_len_number;
    fptr = fopen("flight_schedule.txt","rt");
    if( fptr == NULL )
    {
        printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
        fclose(fptr);
        return -1;
    }
    rewind(fptr);
    flag = 0;
    i = 0;
    // печать рейсов подходящих под введённый пользователем запрос
    while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF )
    {
        if( f[i] == 0 )
        {
            if( flag == 0 )
            {
                printf("\r\n // searching results \r\n\r\n");
                for( int j = 0; j < star; j++ )
                    printf("*");
                printf("\r\n");
                sptr = "Number string";
                distance_between_fields(sptr,&maximum_lengths->MAX_len_number);
                sptr = "1.Flight number";
                distance_between_fields(sptr,&maximum_lengths->MAX_flight_number);
                sptr = "2.Destination";
                distance_between_fields(sptr,&maximum_lengths->MAX_destination);
                sptr = "3.Departure date";
                distance_between_fields(sptr,&maximum_lengths->MAX_departure_date);
                sptr = "4.Departure time";
                distance_between_fields(sptr,&maximum_lengths->MAX_departure_time);
                sptr = "5.Total number of seats";
                distance_between_fields(sptr,&maximum_lengths->MAX_total_number_of_seats);
                sptr = "6.Ticket price";
                distance_between_fields(sptr,&maximum_lengths->MAX_ticket_price);
                printf("\r\n");
                for( int j = 0; j < star; j++ )
                    printf("*");
                printf("\r\n");
                flag = 1;
            }
            printf("#%d",list.number_string);

            if( list.number_string > 0 && list.number_string < 10 )
                print_line_number(2,max);
            else if( list.number_string > 9 && list.number_string < 100 )
                print_line_number(3,max);
            else if( list.number_string > 99 && list.number_string < 1000 )
                print_line_number(4,max);
            else if( list.number_string > 999 && list.number_string < 10000 )
                print_line_number(5,max);
            else if( list.number_string > 9999 && list.number_string < 100000 )
                print_line_number(6,max);

            distance_between_fields(list.flight_number,&maximum_lengths->MAX_flight_number);
            distance_between_fields(list.destination,&maximum_lengths->MAX_destination);
            distance_between_fields(list.departure_date,&maximum_lengths->MAX_departure_date);
            distance_between_fields(list.departure_time,&maximum_lengths->MAX_departure_time);
            distance_between_fields(list.total_number_of_seats,&maximum_lengths->MAX_total_number_of_seats);
            distance_between_fields(list.ticket_price,&maximum_lengths->MAX_ticket_price);
            printf("\r\n");
            for( int j = 0; j < star; j++ )
                printf("*");
            printf("\r\n");
        }
        i++;
    }
    fclose(fptr);
    if( flag == 0 )
        printf("\r\n *** No flights were found by your request! *** \r\n");
}
// печать номера рейса в зависимости от колличества цифр в числе
void print_line_number(int number, int max)
{
    int var; // переменная
    if( max > number )
        var = max - number;
    else
        var = number - max;
    var += 1;
    for( int j = 0; j < var; j++ )
        printf(" ");
    printf("* ");
}
// вывод имеющегося списка рейсов
void display_of_available_flights(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths)
{
    int answer = 0; // ответ пользователя
    do{
        do{
            printf("\r\n ************************************ ");
            printf("\r\n *** Display of available flights *** ");
            printf("\r\n ************************************ \r\n");
            printf("\r\n 1. Print a list of available flights \r\n 2. Go back to the *** Main menu *** \r\n");
            printf("\r\n Indicate the number of what you would like to do (1,2): ");
            scanf("%d",&answer);
            fflush(stdin);
        }while( answer != 1 && answer != 2 );
        if( answer == 1 )
            output(list,maximum_lengths);
    }while( answer != 2 );
}
// редактирование старого списка
int edit_existing_flight_list(int number_of_flights, flight_list list, maximum_lengths_of_flight_positions *maximum_lengths)
{
    int answer = 0; // ответ пользователя
    do{
        if( number_of_flights > 0 )
        {
            do{
                printf("\r\n ********************************* ");
                printf("\r\n *** Edit existing flight list *** ");
                printf("\r\n ********************************* \r\n");
                printf("\r\n 1. Change a specific field \r\n 2. Delete specific flight \r\n 3. Add one or more flights \r\n 4. Go back to the *** Main menu *** \r\n");
                printf("\r\n Indicate the number of what you would like to do (1,2,3,4): ");
                scanf("%d",&answer);
                fflush(stdin);
            }while( answer != 1 && answer != 2 && answer != 3 && answer != 4 );
            if( answer == 1 )
                change_a_specific_field(list,maximum_lengths);
            if( answer == 2 )
                number_of_flights = delete_specific_flight(list,maximum_lengths);
            if( answer == 3 )
                add_one_or_more_flights(list,maximum_lengths);
        }
        else
        {
            printf("\r\n *** The list of flights is empty! *** \r\n");
            answer = 4;
        }
    }while( answer != 4 );
    return number_of_flights;
}
// добавить один или несколько рейсов
void add_one_or_more_flights(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths)
{
    int answer = 0, // ответ пользователя
        enter_number_flights = 0; // число рейсов, которые надо добавить
    do{
        printf("\r\n ******************************* ");
        printf("\r\n *** Add one or more flights *** ");
        printf("\r\n ******************************* \r\n\r\n");
        output(list,maximum_lengths);
        do{
            printf("\r\n Enter the number of flights you want to add (>0): ");
            scanf("%d",&enter_number_flights);
        }while( enter_number_flights < 1 );
        add_flights(enter_number_flights,list);
        do{
            printf("\r\n ******************************* ");
            printf("\r\n *** Add one or more flights *** ");
            printf("\r\n ******************************* \r\n");
            printf("\r\n\r\n // list of newly added flights \r\n\r\n");
            output(list,maximum_lengths);
            printf("\r\n");
            printf("\r\n 1. Add one or more flights \r\n 2. Go back to the *** Edit existing flight list *** \r\n");
            printf("\r\n Indicate the number of what you would like to do (1,2): ");
            scanf("%d",&answer);
            fflush(stdin);
        }while( answer != 1 && answer != 2 );
    }while( answer != 2 );
}
// добавление рейсов
int add_flights(int enter_number_flights,flight_list list)
{
    int flag = 0, // флаг
        counter = 0; // счётчик уже имеющегося числа рейсов
    FILE *fptr;
    fptr = fopen("flight_schedule.txt","rt");
    if( fptr == NULL )
    {
        printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
        fclose(fptr);
        return -1;
    }
    rewind(fptr);
    while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF )
        counter++;
    fclose(fptr);

    enter_number_flights += counter;

    fptr = fopen("flight_schedule.txt","at");
    if( fptr == NULL )
    {
        printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
        fclose(fptr);
        return -1;
    }
    rewind(fptr);
    // добавление новых рейсов
    for( int i = counter; i < enter_number_flights; i++ )
    {
        list.number_string = i+1;
        printf("\r\n *** You enter flight #%d *** \r\n", i+1);
        do{
            printf("\r\n Enter flight number: ");
            scanf("%s",list.flight_number);
            fflush(stdin);
        }while( letter_entry_protection(list.flight_number) );
        printf("\r\n Enter destination: ");
        scanf("%s",list.destination);
        fflush(stdin);
        do{
            printf("\r\n Enter departure date (dd.mm.yyyy): ");
            scanf("%s",list.departure_date);
            fflush(stdin);
            if( strlen(list.departure_date) != 10 )
                flag = 1;
            else
                if( list.departure_date[2] != '.' || list.departure_date[5] != '.' )
                    flag = 1;
                else
                    flag = 0;
        }while( letter_entry_protection(list.departure_date) || flag == 1 );
        do{
            printf("\r\n Enter departure time: ");
            scanf("%s",list.departure_time);
            fflush(stdin);
        }while( letter_entry_protection(list.departure_time) );
        do{
            printf("\r\n Enter total number of seats: ");
            scanf("%s",list.total_number_of_seats);
            fflush(stdin);
        }while( letter_entry_protection(list.total_number_of_seats) );
        do{
            printf("\r\n Enter ticket price: ");
            scanf("%s",list.ticket_price);
            fflush(stdin);
        }while( letter_entry_protection(list.ticket_price) );
        printf("\r\n");
        fprintf(fptr," %d %s %s %s %s %s %s ",list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price);
    }
    fclose(fptr);
}
// удалить определённый рейс
int delete_specific_flight(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths)
{
    int answer = 0, // ответ пользователя
        flag = 0, // флаг
        enter_number_string = 0, // номер строки, которую ввёл пользователь
        counter = 0, // счётчие рейсов в базе данных
        variable = 0; // переменная
    FILE *fptr, *fnew;

    do{
        fptr = fopen("flight_schedule.txt","rt");
        if( fptr == NULL )
        {
            printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
            fclose(fptr);
            return -1;
        }
        printf("\r\n ****************************** ");
        printf("\r\n *** Delete specific flight *** ");
        printf("\r\n ****************************** \r\n\r\n");
        printf(" *** If you not want delete string, when enter number -1 *** \r\n\r\n");
        variable = output(list,maximum_lengths);
        do{
            flag = 0;
            printf("\r\n Enter number string: ");
            fflush(stdin);
            scanf("%d",&enter_number_string);
            if( enter_number_string == -1 )
            {
                fclose(fptr);
            	return variable;
            }
            fflush(stdin);
            rewind(fptr);
            while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF )
                if( list.number_string == enter_number_string )
                {
                    flag = 1;
                    break;
                }
            if( flag == 0 )
                printf("\r\n *** You entered an invalid line number. Try again! *** \r\n");
        }while( flag == 0 );

        rewind(fptr);
        fnew = fopen("new.txt","wt");
        if( fnew == NULL )
        {
            printf("\r\n *** File new.txt not open! *** \r\n");
            fclose(fnew);
            return -2;
        }
        rewind(fnew);
        counter = 0;
        while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF )
            if( list.number_string != enter_number_string )
            {
                fprintf(fnew," %d %s %s %s %s %s %s ",list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price);
                counter++;
            }
        fclose(fnew);
        fclose(fptr);
        remove("flight_schedule.txt");
        rename("new.txt","flight_schedule.txt");
        
        if( counter != 0 )
        {
            do{
                printf("\r\n\r\n // amended list \r\n\r\n");
                variable = output(list,maximum_lengths);
                printf("\r\n");
                printf("\r\n 1. Delete another flight \r\n 2. Go back to the *** Edit existing flight list *** \r\n");
                printf("\r\n Indicate the number of what you would like to do (1,2): ");
                scanf("%d",&answer);
                fflush(stdin);
            }while( answer != 1 && answer != 2 );
        }
        else
        {
            do{
                printf("\r\n\r\n // amended list \r\n\r\n");
                variable = output(list,maximum_lengths);
                printf("\r\n");
                printf("\r\n *** Flight list is empty *** \r\n 1. Go back to the *** Main menu *** \r\n");
                printf("\r\n Indicate the number of what you would like to do (1): ");
                scanf("%d",&answer);
                fflush(stdin);
            }while( answer != 1 );
            answer = 2;
        }
    }while( answer != 2 );
    return variable;
}
// изменить определенное поле
int change_a_specific_field(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths)
{
    char    enter_new_information[SIZE] = {}; // строка, в которую помещается введённая пользователем новая информация
    int     flag = 0, // флаг
            enter_number_string = 0, // номер строки, в которой пользователь хочет изменить информацию
            answer = 0, // ответ пользователя
            enter_field_number = 0 // номер поля, в котором пользователь хочет изменить информацию
    ;
    FILE *fptr, *fnew;
    do{
        fptr = fopen("flight_schedule.txt","rt");
        if( fptr == NULL )
        {
            printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
            fclose(fptr);
            return -1;
        }
        printf("\r\n ******************************* ");
        printf("\r\n *** Change a specific field *** ");
        printf("\r\n ******************************* \r\n\r\n");
        output(list,maximum_lengths);
        do{
            flag = 0;
            printf("\r\n Enter number string: ");
            scanf("%d",&enter_number_string);
            fflush(stdin);
            rewind(fptr);
            while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF )
                if( list.number_string == enter_number_string )
                {
                    flag = 1;
                    break;
                }
            if( flag == 0 )
                printf("\r\n *** You entered an invalid line number. Try again! *** \r\n");
        }while( flag == 0 );

        rewind(fptr);

        do{
            printf("\r\n Enter field number (1,2,3,4,5,6): ");
            scanf("%d",&enter_field_number);
            fflush(stdin);
        }while( enter_field_number != 1 && enter_field_number != 2 && enter_field_number != 3 && enter_field_number != 4 && enter_field_number != 5 && enter_field_number != 6 );

        fnew = fopen("new.txt","wt");
        if( fnew == NULL )
        {
            printf("\r\n *** File new.txt not open! *** \r\n");
            fclose(fnew);
            return -2;
        }
        while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF)
        {
            if( list.number_string == enter_number_string )
                switch(enter_field_number)
                {
                    case 1:
                        replacement_of_information(list.flight_number,enter_field_number);
                        break;
                    case 2:
                        replacement_of_information(list.destination,enter_field_number);
                        break;
                    case 3:
                        replacement_of_information(list.departure_date,enter_field_number);
                        break;
                    case 4:
                        replacement_of_information(list.departure_time,enter_field_number);
                        break;
                    case 5:
                        replacement_of_information(list.total_number_of_seats,enter_field_number);
                        break;
                    case 6:
                        replacement_of_information(list.ticket_price,enter_field_number);
                        break;
                }
            fprintf(fnew," %d %s %s %s %s %s %s ",list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price);
        }
        fclose(fnew);
        fclose(fptr);
        remove("flight_schedule.txt");
        rename("new.txt","flight_schedule.txt");
        do{
            printf("\r\n\r\n // amended list \r\n\r\n");
            output(list,maximum_lengths);
            printf("\r\n");
            printf("\r\n 1. Edit another specific field \r\n 2. Go back to the *** Edit existing flight list *** \r\n");
            printf("\r\n Indicate the number of what you would like to do (1,2): ");
            scanf("%d",&answer);
            fflush(stdin);
        }while( answer != 1 && answer != 2 );
    }while( answer != 2 );
}
// замена информации
void replacement_of_information(char string[], int position)
{
    fflush(stdin);
    int flag = 0;
    for( int j = 0; j < SIZE; j++ )
        string[j] = 0;
    switch(position)
    {
        case 1:
            do{
                printf("\r\n Enter new flight number: ");
                scanf("%s",string);
                fflush(stdin);
            }while( letter_entry_protection(string) );
            break;
        case 2:
            printf("\r\n Enter new destination: ");
            scanf("%s",string);
            fflush(stdin);
            break;
        case 3:
            do{
                printf("\r\n Enter new departure date (dd.mm.yyyy): ");
                scanf("%s",string);
                fflush(stdin);
                if( strlen(string) != 10 )
                    flag = 1;
                else
                    if( string[2] != '.' || string[5] != '.' )
                        flag = 1;
                    else
                        flag = 0;
            }while( letter_entry_protection(string) || flag == 1 );
            break;
        case 4:
            do{
                printf("\r\n Enter new departure time: ");
                scanf("%s",string);
                fflush(stdin);
            }while( letter_entry_protection(string) );
            break;
        case 5:
            do{
                printf("\r\n Enter new total number of seats: ");
                scanf("%s",string);
                fflush(stdin);
            }while( letter_entry_protection(string) );
            break;
        case 6:
            do{
                printf("\r\n Enter new ticket price: ");
                scanf("%s",string);
                fflush(stdin);
            }while( letter_entry_protection(string) );
            break;
    }
}
// вывод списка рейсов
int output(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths)
{
    int star = 0, // звезда, переменная показывающая количество печатаемыз звёзд
        counter = 0, // считает количество рейсов в базе данных
        max = 0; // максимальная длинна номера строки
    char *sptr;
    maximum_field_length(list,maximum_lengths);
    star = maximum_lengths->MAX_len_number + maximum_lengths->MAX_flight_number + maximum_lengths->MAX_destination + maximum_lengths->MAX_departure_date + maximum_lengths->MAX_departure_time + maximum_lengths->MAX_total_number_of_seats + maximum_lengths->MAX_ticket_price;
    star += 20;
    max = maximum_lengths->MAX_len_number;
    for( int j = 0; j < star; j++ )
        printf("*");
    printf("\r\n");
    sptr = "Number string";
    distance_between_fields(sptr,&maximum_lengths->MAX_len_number);
    sptr = "1.Flight number";
    distance_between_fields(sptr,&maximum_lengths->MAX_flight_number);
    sptr = "2.Destination";
    distance_between_fields(sptr,&maximum_lengths->MAX_destination);
    sptr = "3.Departure date";
    distance_between_fields(sptr,&maximum_lengths->MAX_departure_date);
    sptr = "4.Departure time";
    distance_between_fields(sptr,&maximum_lengths->MAX_departure_time);
    sptr = "5.Total number of seats";
    distance_between_fields(sptr,&maximum_lengths->MAX_total_number_of_seats);
    sptr = "6.Ticket price";
    distance_between_fields(sptr,&maximum_lengths->MAX_ticket_price);
    printf("\r\n");
    for( int j = 0; j < star; j++ )
        printf("*");
    printf("\r\n");

    FILE * fptr;
    fptr = fopen("flight_schedule.txt","rt");
    if( fptr == NULL )
    {
        printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
        fclose(fptr);
        return -1;
    }
    rewind(fptr);
    counter = 0;
    while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF )
    {
        counter++;
        printf("#%d",list.number_string);
        if( list.number_string > 0 && list.number_string < 10 )
            print_line_number(2,max);
        else if( list.number_string > 9 && list.number_string < 100 )
            print_line_number(3,max);
        else if( list.number_string > 99 && list.number_string < 1000 )
            print_line_number(4,max);
        else if( list.number_string > 999 && list.number_string < 10000 )
            print_line_number(5,max);
        else if( list.number_string > 9999 && list.number_string < 100000 )
            print_line_number(6,max);
        distance_between_fields(list.flight_number,&maximum_lengths->MAX_flight_number);
        distance_between_fields(list.destination,&maximum_lengths->MAX_destination);
        distance_between_fields(list.departure_date,&maximum_lengths->MAX_departure_date);
        distance_between_fields(list.departure_time,&maximum_lengths->MAX_departure_time);
        distance_between_fields(list.total_number_of_seats,&maximum_lengths->MAX_total_number_of_seats);
        distance_between_fields(list.ticket_price,&maximum_lengths->MAX_ticket_price);
        printf("\r\n");
        for( int j = 0; j < star; j++ )
            printf("*");
        printf("\r\n");
    }
    fclose(fptr);
    return counter;
}
// расстояние между полями
void distance_between_fields(char string[], int *max)
{
    int var = 0;
    printf("%s",string);
    var = (*max) - strlen(string);
    var += 1;
    for( int j = 0; j < var; j++ )
        printf(" ");
    printf("* ");
}
// заполнение структуры максимальных значений полей
int maximum_field_length(flight_list list, maximum_lengths_of_flight_positions *maximum_lengths)
{
    maximum_lengths->MAX_len_number = strlen("Number string");
    maximum_lengths->MAX_flight_number = strlen("1.Flight number");
    maximum_lengths->MAX_destination = strlen("2.Destination");
    maximum_lengths->MAX_departure_date = strlen("3.Departure date");
    maximum_lengths->MAX_departure_time = strlen("4.Departure time");
    maximum_lengths->MAX_total_number_of_seats = strlen("5.Total number of seats");
    maximum_lengths->MAX_ticket_price = strlen("6.Ticket price");

    FILE * fptr;
    fptr = fopen("flight_schedule.txt","rt");
    if( fptr == NULL )
    {
        printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
        fclose(fptr);
        return -1;
    }
    rewind(fptr);
    while( fscanf(fptr,"%d%s%s%s%s%s%s",&list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price) != EOF )
    {
        identification_of_the_maximum_value(list.flight_number,&maximum_lengths->MAX_flight_number);
        identification_of_the_maximum_value(list.destination,&maximum_lengths->MAX_destination);
        identification_of_the_maximum_value(list.departure_date,&maximum_lengths->MAX_departure_date);
        identification_of_the_maximum_value(list.departure_time,&maximum_lengths->MAX_departure_time);
        identification_of_the_maximum_value(list.total_number_of_seats,&maximum_lengths->MAX_total_number_of_seats);
        identification_of_the_maximum_value(list.ticket_price,&maximum_lengths->MAX_ticket_price);
    }
    fclose(fptr);
}
// выявление максимального значения
void identification_of_the_maximum_value(char string[],int *max)
{
    if( (*max) < strlen(string) )
        (*max) = strlen(string);
}
// создание нового списка рейсов
int create_a_new_flight_list(flight_list list)
{
    int answer = 0, // ответ пользователя
        number_of_flights = 0; // число рейсов, которые пользователь хочет поместить в базу данных
    do{
        do{
            printf("\r\n ******************************** ");
            printf("\r\n *** Create a new flight list *** ");
            printf("\r\n ******************************** \r\n");
            printf("\r\n 1. Enter number of flights \r\n 2. Go back to the *** Main menu *** \r\n");
            printf("\r\n Indicate the number of what you would like to do (1,2): ");
            scanf("%d",&answer);
            fflush(stdin);
        }while( answer != 1 && answer != 2 );
        if( answer == 1 )
        {
            printf("\r\n ****************************** ");
            printf("\r\n *** Enter number of flights*** ");
            printf("\r\n ****************************** \r\n");
            do{
                printf("\r\n The number of your flights is equal (>0): ");
                scanf("%d",&number_of_flights);
                fflush(stdin);
            }while( number_of_flights < 1);
            input(number_of_flights,list);
        }
    }while( answer != 2 );

    return number_of_flights;
}
// заполнение списка рейсов
int input(int number_of_flights,flight_list list)
{
    int flag = 0;
    FILE *fptr;
    fptr = fopen("flight_schedule.txt","wt");
    if( fptr == NULL )
    {
        printf("\r\n *** File flight_schedule.txt not open! *** \r\n");
        fclose(fptr);
        return -1;
    }
    for( int i = 0; i < number_of_flights; i++ )
    {
        list.number_string = i+1;
        printf("\r\n *** You enter flight #%d *** \r\n", i+1);
        do{
            printf("\r\n Enter flight number: ");
            scanf("%s",list.flight_number);
            fflush(stdin);
        }while( letter_entry_protection(list.flight_number) );
        printf("\r\n Enter destination: ");
        scanf("%s",list.destination);
        fflush(stdin);
        do{
            printf("\r\n Enter departure date (dd.mm.yyyy): ");
            scanf("%s",list.departure_date);
            fflush(stdin);
            if( strlen(list.departure_date) != 10 )
                flag = 1;
            else
                if( list.departure_date[2] != '.' || list.departure_date[5] != '.' )
                    flag = 1;
                else
                    flag = 0;
        }while( letter_entry_protection(list.departure_date) || flag == 1 );
        do{
            printf("\r\n Enter departure time: ");
            scanf("%s",list.departure_time);
            fflush(stdin);
        }while( letter_entry_protection(list.departure_time) );
        do{
            printf("\r\n Enter total number of seats: ");
            scanf("%s",list.total_number_of_seats);
            fflush(stdin);
        }while( letter_entry_protection(list.total_number_of_seats) );
        do{
            printf("\r\n Enter ticket price: ");
            scanf("%s",list.ticket_price);
            fflush(stdin);
        }while( letter_entry_protection(list.ticket_price) );
        printf("\r\n");
        fprintf(fptr," %d %s %s %s %s %s %s ",list.number_string,list.flight_number,list.destination,list.departure_date,list.departure_time,list.total_number_of_seats,list.ticket_price);
    }
    fclose(fptr);
}
// защита от ввода букв
int letter_entry_protection(char string[])
{
    int    x = 0,   // длинна полученной строки
          ok = 0;   // возвращаемое значение
    x = strlen(string);
    ok = 0;
    for( int i = 0; i < x; i++ )
        if( string[i] < 46 || string[i] > 58 || string[i] == 47 )
        {
            ok = 1;
            break;
        }
    return ok;
}