#include <stdio.h>

/*Function to get the first initial of a person with the given ID*/
char first_initial(FILE *id_fp, int id)
{
    int current_id;
    char first_name;
    rewind(id_fp); /* Start from the beginning of the file*/
    while (fscanf(id_fp, "%d;%c", &current_id, &first_name) != EOF)
    {
        if (current_id == id)
        {
            return first_name;
        }
        /*Skip to the next line*/
        while (fgetc(id_fp) != '\n')
            ;
    }
    return '\0'; /* ID not found*/
}

/*Function to get the last initial of a person with the given ID*/
char last_initial(FILE *id_fp, int id)
{
    int current_id;
    char last_name;
    rewind(id_fp);
    while (fscanf(id_fp, "%d;%*c;%c", &current_id, &last_name) != EOF)
    {
        if (current_id == id)
        {
            return last_name;
        }
        /*Skip to the next line*/
        while (fgetc(id_fp) != '\n')
            ;
    }
    return '\0'; /*ID not found*/
}

/*Function to get the ID of a person with the given first initial*/
int get_id_fi(FILE *id_fp, char first_initial)
{
    int current_id;
    char current_fi;
    rewind(id_fp);
    while (fscanf(id_fp, "%d;%c", &current_id, &current_fi) != EOF)
    {
        if (current_fi == first_initial)
        {
            return current_id;
        }
        /*Skip to the next line*/
        else
        {
            while (fgetc(id_fp) != '\n')
                ;
        }
    }
    return -1; /*ID not found*/
}

/*Function to get the ID of a person with the given last initial*/
int get_id_li(FILE *id_fp, char last_initial)
{
    int current_id;
    char current_li;
    rewind(id_fp);
    while (fscanf(id_fp, "%d;%c", &current_id, &current_li) != EOF)
    {
        if (current_li == last_initial)
        {
            return current_id;
        }
        /*Skip to the next line*/
        while (fgetc(id_fp) != '\n')
            ;
    }
    return -1; /*ID not found*/
}
char calculate_letter_grade(float average)
{
    if (average >= 90)
    {
        return 'A';
    }
    else if (average >= 80)
    {
        return 'B';
    }
    else if (average >= 70)
    {
        return 'C';
    }
    else if (average >= 60)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

/*Function to calculate the GPA of a student with the given ID*/
float average_grade(FILE *info_fp, int id)
{
    int current_id = 0, midterm1 = 0, midterm2 = 0, final = 0, course_id = 0;
    float average;
    char counter;
    char c;
    int class_counter = 0;
    int ret_val = 0;

    rewind(info_fp);

    while (fscanf(info_fp, "%d", &current_id) == 1)
    {
        if (current_id == id)
        {
            ret_val = fscanf(info_fp, ";%d;%d;%d;%d", &midterm1, &midterm2, &final, &course_id);
            if (ret_val == 4)
            {
                average = (midterm1 + midterm2) / 2;
            }
            else if (ret_val == 3)
            {

                average = midterm1;
            }
            else
            {
                break;
            }

            return average;
        }
        else
        {

            while (c = fgetc(info_fp))
            {
                if (c == '\n')
                {
                    break;
                }
            }; /*Skip to the next line*/
        }
    }

    return -1; /*ID not found*/
}

int main()
{
    FILE *id_fp = fopen("first.txt", "r");
    FILE *info_fp = fopen("second.txt", "r");

    int midterm1, midterm2, final, course_id;

    if (id_fp == NULL || info_fp == NULL)
    {
        printf("Error opening files.\n");
        return 1;
    }

    char choice;

    int id = 0;
    int id1 = 0;
    int id2 = 0;
    int id4 = 0;
    int std_id = 0;
    char first_initial;
    int flag = 1;

    while (flag)
    {
        printf("\nMenu:\n");
        printf("p: Print all users pass or fail\n");
        printf("n: Print only the user with a specific first initial\n");
        printf("g: Calculate the GPA of a given student\n");
        printf("c: Print whether each user passed or failed the same class\n");
        printf("t: Print the number of classes for the instructor\n");
        printf("d: Print the department of all persons according to the role\n");
        printf("l: Print the course_id of a given student\n");
        printf("e: Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'p':
            /* Print all users pass or fail */
            rewind(id_fp);
            while (fscanf(id_fp, "%d;%d;%d;%d;%d", &id, &midterm1, &midterm2, &final, &course_id) != EOF)
            {
                float average = average_grade(id_fp, id);
                char letter_grade = calculate_letter_grade(average);
                printf("ID: %d, Letter Grade: %c\n", id, letter_grade);
            }
            break;

        case 'n':
            /* Print only the user with a specific first initial*/
            printf("Enter the first initial: \n");
            scanf(" %c", &first_initial);
            id1 = get_id_fi(id_fp, first_initial);
            printf("%d", id1);
            if (id1 != -1)
            {
                printf("error");
            }
            else
            {
                printf("User with first initial '%c' not found.\n", first_initial);
            }
            break;

        case 'g':

            /*Calculate the GPA of a given student*/
            printf("Enter the student ID: ");
            scanf("%d", &id2);
            float average = average_grade(info_fp, id2);
            if (average != -1)
            {
                printf("GPA for student %d: %.2f\n", id2, average);
            }
            else
            {
                printf("Student with ID %d not found.\n", id2);
            }
            break;
            /*... (implement other cases similarly)*/

        case 'l':
            printf("Enter the student ID: ");
            scanf("%d", &std_id);
            while (fscanf(id_fp, "%d;%d;%d;%d;%d", &id4, &midterm1, &midterm2, &final, &course_id) != EOF)
            {
                id4 = std_id;
                printf("%d", course_id);
            }

            break;
        case 'e':
            flag = 0;
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }
    }

    fclose(id_fp);
    fclose(info_fp);
    return 0;
}
