#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1000
int login_succes = 0;

char *customer_email;
int complaint_id;
char *response;



typedef struct
{
    int policy_id;
    char policy_type[50];
    float coverage_details;
    float premium_amount;
    char start_date[10];
    char end_date[10];
    char user_email[100];
} Policy;

Policy policies[100];
int num_policies = 0;



void create_policy()
{
    if (num_policies >= 100)
    {
        printf("Cannot create more policies. Maximum limit reached.\n");
        return;
    }

    Policy new_policy;

    printf("Enter Policy Type: ");
    scanf("%s", new_policy.policy_type);

    printf("Enter Coverage Details: ");
    scanf("%f", &new_policy.coverage_details);

    printf("Enter Premium Amount: ");
    scanf("%f", &new_policy.premium_amount);

    printf("Enter Start Date (YYYY-MM-DD): ");
    scanf("%s", new_policy.start_date);
    int count2 =0;
    int check_dash=0;
for(int i=0;i<10;i++){
        if(new_policy.start_date[i]=='-'){
            check_dash++;
        }
    if(new_policy.start_date[i]>='0'&&new_policy.start_date[i]<='9'){
        count2++;
        continue;
    }
    if(new_policy.start_date[i]=='-'&&i==4){
        if(count2==4){
            count2=0;
            continue;
        }else{
        printf("wrong start date\n");
        create_policy();
        }
        continue;
    }else if(new_policy.start_date[i]=='-'&&(i==6||i==7)){
    if(count2==1||count2==2){
    count2=0;
    continue;
    }else{
    printf("wrong start date\n");
    create_policy();
    }
    }else if(new_policy.start_date[5]=='-'){
    printf("wrong start date\n");
        create_policy();
    }
    else if(i==8||i==9){
    if(count2==1||count2==2){
    count2=0;
    break;
    }else{
    printf("wrong start date\n");
    create_policy();
    }
    }
    if(check_dash<1){
        printf("wrong start date\n");
        create_policy();
    }
}
    printf("Enter End Date (YYYY-MM-DD): ");
    scanf("%s", new_policy.end_date);
int check_dash2=0;
int count3=0;
for(int i=0;i<10;i++){
        if(new_policy.end_date[i]=='-'){
            check_dash2++;
        }
    if(new_policy.end_date[i]>='0'&&new_policy.end_date[i]<='9'){
        count3++;
        continue;
    }
    if(new_policy.end_date[i]=='-'&&i==4){
        if(count3==4){
            count3=0;
            continue;
        }else{
        printf("wrong end date\n");
        create_policy();
        }
        continue;
    }else if(new_policy.end_date[i]=='-'&&(i==6||i==7)){
    if(count3==1||count3==2){
    count3=0;
    continue;
    }else{
    printf("wrong end date\n");
    create_policy();
    }
    }else if(new_policy.end_date[5]=='-'){
    printf("wrong end date\n");
        create_policy();
    }
    else if(i==8||i==9){
    if(count3==1||count3==2){
    count3=0;
    break;
    }else{
    printf("wrong end date\n");
    create_policy();
    }
    }
    if(check_dash2<1){
        printf("wrong end date\n");
        create_policy();
    }
}
    printf("Enter user email: ");
    scanf("%s", new_policy.user_email);

    printf("Policy created successfully.\n");


    FILE *polices = fopen("polices.csv", "a+");


    int count = 0;
    char c;


    for (c = getc(polices); c != EOF; c = getc(polices))
        if (c == '\n')
            count = count + 1;


    fprintf(polices, "%i,%s,%g,%g,%s,%s,%s\n",
            count,
            new_policy.policy_type,
            new_policy.coverage_details,
            new_policy.premium_amount,
            new_policy.start_date,
            new_policy.end_date,
            new_policy.user_email);
    printf("Policy was added to the file.\n");

    fclose(polices);
}

void display_policies(char *customer_email)
{

    FILE* polices = fopen("polices.csv", "r");
    if (polices == NULL)
    {
        printf("Failed to open file.\n");

    }

    int index = 0;
    char line[256];
    while (fgets(line, sizeof(line), polices))
    {
        Policy policy;
        sscanf(line, "%d,%[^,],%f,%f,%[^,],%[^,],%[^\n]",
               &policy.policy_id, policy.policy_type, &policy.coverage_details,
               &policy.premium_amount, policy.start_date, policy.end_date, policy.user_email);

        if(strcmp(policy.user_email , customer_email)==0){

        policies[index++] = policy;}
        if (index >= 100)
        {
            printf("Reached maximum number of policies.\n");
            break;
        }
    }




    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("ID  | Policy Type          |  Coverage Details | Premium Amount | Start Date   | End Date     | user email\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < index; ++i)
    {
        printf("%-4i| %-21s| %-18.2f| %-15.2f| %-13s| %-13s| %-s\n",
               policies[i].policy_id,
               policies[i].policy_type,
               policies[i].coverage_details,
               policies[i].premium_amount,
               policies[i].start_date,
               policies[i].end_date,
               policies[i].user_email);
    }

    printf("----------------------------------------------------------------------------------------------------------\n");


}
void view_policies() {

    FILE* file = fopen("polices.csv", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return -1;
    }

    int index = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Policy policy;
        sscanf(line, "%d,%[^,],%f,%f,%[^,],%[^,],%[^\n]",
               &policy.policy_id, policy.policy_type, &policy.coverage_details,
               &policy.premium_amount, policy.start_date, policy.end_date, policy.user_email);
        policies[index++] = policy;
        if (index >= 100) {
            printf("Reached maximum number of policies.\n");
            break;
        }
    }

    fclose(file);


    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("ID  | Policy Type          |  Coverage Details | Premium Amount | Start Date   | End Date     | Beneficiary\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < index; ++i) {
        printf("%-4i| %-21s| %-18.2f| %-15.2f| %-13s| %-13s| %-s\n",
               policies[i].policy_id,
               policies[i].policy_type,
               policies[i].coverage_details,
               policies[i].premium_amount,
               policies[i].start_date,
               policies[i].end_date,
               policies[i].user_email);
    }

    printf("----------------------------------------------------------------------------------------------------------\n");

}
void edit_policy() {
    int policy_id;
    printf("Enter Policy ID to edit: ");
    scanf("%d", &policy_id);

    FILE *polices = fopen("polices.csv", "a+");
    if (polices == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    int index = 0;
    char line[256];
    while (fgets(line, sizeof(line), polices)) {
        Policy policy;
        sscanf(line, "%d,%[^,],%f,%f,%[^,],%[^,],%[^\n]",
               &policy.policy_id, policy.policy_type, &policy.coverage_details,
               &policy.premium_amount, policy.start_date, policy.end_date, policy.user_email);
        policies[index++] = policy;
    }
    fclose(polices);

    int found = 0;
    int idx=0;
    for (int i = 0; i < index; ++i) {
        if (policies[i].policy_id == policy_id) {
            found = 1;

            printf("Editing Policy ID %d\n", policy_id);
            printf("Enter new Policy Type (current: %s): ", policies[i].policy_type);
            scanf("%s", policies[i].policy_type);
            printf("Enter new Coverage Details (current: %.2f): ", policies[i].coverage_details);
            scanf("%f", &policies[i].coverage_details);
            printf("Enter new Premium Amount (current: %.2f): ", policies[i].premium_amount);
            scanf("%f", &policies[i].premium_amount);
            printf("Enter new Start Date (current: %s): ", policies[i].start_date);
            scanf("%s", policies[i].start_date);
            int count2 =0;
    int check_dash=0;
for(int g=0;g<10;g++){
        if(policies[i].start_date[g]=='-'){
            check_dash++;
        }
    if(policies[i].start_date[g]>='0'&&policies[i].start_date[g]<='9'){
        count2++;
        continue;
    }
    if(policies[i].start_date[g]=='-'&&g==4){
        if(count2==4){
            count2=0;
            continue;
        }else{
        printf("wrong start date\n");
        edit_policy();
        }
        continue;
    }else if(policies[i].start_date[g]=='-'&&(g==6||g==7)){
    if(count2==1||count2==2){
    count2=0;
    continue;
    }else{
    printf("wrong start date\n");
    edit_policy();
    }
    }else if(policies[i].start_date[5]=='-'){
    printf("wrong start date\n");
        edit_policy();
    }
    else if(g==8||g==9){
    if(count2==1||count2==2){
    count2=0;
    break;
    }else{
    printf("wrong start date\n");
    edit_policy();
    }
    }
    if(check_dash<1){
        printf("wrong start date\n");
        edit_policy();
    }
}
            printf("Enter new End Date (current: %s): ", policies[i].end_date);
            scanf("%s", policies[i].end_date);
           int check_dash2=0;
int count3=0;
for(int g=0;g<10;g++){
        if(policies[i].end_date[g]=='-'){
            check_dash2++;
        }
    if(policies[i].end_date[g]>='0'&&policies[i].end_date[g]<='9'){
        count3++;
        continue;
    }
    if(policies[i].end_date[g]=='-'&&i==4){
        if(count3==4){
            count3=0;
            continue;
        }else{
        printf("wrong end date\n");
        edit_policy();
        }
        continue;
    }else if(policies[i].end_date[g]=='-'&&(i==6||i==7)){
    if(count3==1||count3==2){
    count3=0;
    continue;
    }else{
    printf("wrong end date\n");
    create_policy();
    }
    }else if(policies[i].end_date[5]=='-'){
    printf("wrong end date\n");
        edit_policy();
    }
    else if(i==8||i==9){
    if(count3==1||count3==2){
    count3=0;
    break;
    }else{
    printf("wrong end date\n");
    edit_policy();
    }
    }
    if(check_dash2<1){
        printf("wrong end date\n");
        edit_policy();
    }
}
            printf("Enter new user_email (current: %s): ", policies[i].user_email);
            scanf("%s", policies[i].user_email);
            printf("Policy updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Policy with ID %d not found.\n", policy_id);
        return;
    }

    polices = fopen("polices.csv", "w");
    if (polices == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    for (int i = 0; i < index; ++i) {
        fprintf(polices, "%d,%s,%g,%g,%s,%s,%s\n",
                policies[i].policy_id,
                policies[i].policy_type,
                policies[i].coverage_details,
                policies[i].premium_amount,
                policies[i].start_date,
                policies[i].end_date,
                policies[i].user_email);
    }

    fclose(polices);}

void clear_console()
{
    printf("\e[1;1H\e[2J");
}
int admin_login()
{
    struct user_regester
    {
        char email[150];
        char pass[20];
    };
    struct user_regester user_info = {'0', '0', '0'};
    printf("Enter your email: ");
    scanf("%s", &user_info.email);
    printf("Enter your password: ");
    scanf("%s", &user_info.pass);
    FILE *users_file;
    users_file = fopen("users_info.csv", "r");
    char fileinfo[1000000];
    fgets(fileinfo, 1000000, users_file);
    char line[MAX_LINE_LENGTH];
    int check = 0;
    while (fgets(line, sizeof(line), users_file) != NULL)
    {

        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, user_info.email) == 0)
        {
            check++;
        }
        if (check == 1)
        {
            if (strcmp(line, user_info.pass) == 0)
            {
                check++;
            }
            if (check == 2)
            {
                break;
            }
        }
    }
    if (check == 2)
    {
        if (user_info.email[0] == 'a' && user_info.email[1] == 'd' && user_info.email[2] == 'm' && user_info.email[3] == 'i' && user_info.email[4] == 'n')
        {
            login_succes = 1;
            clear_console();
            printf("login successfuly!\nHello: ");
            for (int i = 0; i < 150; i++)
            {
                if (user_info.email[i] == '@')
                {
                    break;
                }
                printf("%c", user_info.email[i]);
            }
            printf("\n");
        }
        else
        {
            printf("Wrong email or password!\n");
            admin_login();
        }
    }
    else
    {
        clear_console();
        printf("Wrong email or password!\n");
        admin_login();
    }
    fclose(users_file);
    return 0;
}
int user_login()
{
    struct user_regester
    {
        char email[150];
        char pass[20];
    };
    struct user_regester user_info = {'0', '0', '0'};
    printf("Enter your email: ");
    scanf("%s", &user_info.email);
    customer_email = user_info.email;

    printf("Enter your password: ");
    scanf("%s", &user_info.pass);
    FILE *users_file;
    users_file = fopen("users_info.csv", "r");
    char fileinfo[1000000];
    fgets(fileinfo, 1000000, users_file);
    char line[MAX_LINE_LENGTH];
    int check = 0;
    while (fgets(line, sizeof(line), users_file) != NULL)
    {

        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, user_info.email) == 0)
        {
            check = 1;
        }
        if (check == 1)
        {
            if (strcmp(line, user_info.pass) == 0)
            {
                check = 2;
            }
            if (check == 2)
            {
                break;
            }
        }
    }
    if (check == 2)
    {
        if (!(user_info.email[0] == 'a' && user_info.email[1] == 'd' && user_info.email[2] == 'm' && user_info.email[3] == 'i' && user_info.email[4] == 'n'))
        {
            clear_console();
            printf("login successfuly!\nHello: ");

            for (int i = 0; i < 150; i++)
            {
                if (user_info.email[i] == '@')
                {
                    break;
                }
                printf("%c", user_info.email[i]);
            }
            printf("\n");
            login_succes = 3;
        }
        else
        {
            printf("Wrong email or password!\n");
            user_login();
        }
    }
    else
    {
        clear_console();
        printf("Wrong email or password!\n");
        user_login();
    }
    fclose(users_file);
    return 0;
}

void agent_login()
{
    struct user_regester
    {
        char email[150];
        char pass[20];
    };
    struct user_regester user_info = {'0', '0', '0'};
    printf("Enter your email: ");
    scanf("%s", &user_info.email);
    printf("Enter your password: ");
    scanf("%s", &user_info.pass);
    FILE *users_file;
    users_file = fopen("agent_info.csv", "r");
    char fileinfo[1000000];
    fgets(fileinfo, 1000000, users_file);
    char line[MAX_LINE_LENGTH];
    int check = 0;
    while (fgets(line, sizeof(line), users_file) != NULL)
    {

        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, user_info.email) == 0)
        {
            check = 1;
        }
        if (check == 1)
        {
            if (strcmp(line, user_info.pass) == 0)
            {
                check = 2;
            }
            if (check == 2)
            {
                break;
            }
        }
    }
    if (check == 2)
    {
        clear_console();
        printf("login successfuly!\nHello: ");
        for (int i = 0; i < 150; i++)
        {
            if (user_info.email[i] == '@')
            {
                break;
            }
            printf("%c", user_info.email[i]);
        }
        printf("\n");
        login_succes = 2;
    }
    else
    {
        clear_console();
        printf("Wrong email or password!\n");
        agent_login();
    }
    fclose(users_file);
}
int regester()
{
    clear_console();
    struct user_regester
    {
        char email[150];
        char pass[20];
        char cpass[20];
    };
    struct user_regester user_info = {'0', '0', '0'};
    printf("///////////////////////////// The rules of writing a TRUE email & password /////////////////////////////\nFor Email!\n[1] Email must contain '@' and '.'\nExample(email@gmail.com)\nFor Password!\n[1] The password must contain at least 1 special character\n[2] The password must contain at least 1 number\n[3] The Password must include normal characters\n[4] The length of the password at least 6 characters\n");
    printf("Enter your email: ");
    scanf("%s", &user_info.email);
    printf("Enter your password: ");
    scanf("%s", &user_info.pass);
    printf("Confirm your password: ");
    scanf("%s", &user_info.cpass);
    FILE *users_file;
    users_file = fopen("users_info.csv", "r");
    char fileinfo[1000000];
    fgets(fileinfo, 1000000, users_file);
    char line[MAX_LINE_LENGTH];
    int check_email = 0;
    int check_pass_letter = 0;
    int check_pass_num = 0;
    int check_pass_length = 0;
    int check_pass_special = 0;
    int check_cpass = 0;
    for (int i = 0; i < 150; i++)
    {
        if (user_info.email[i] == '@')
        {
            check_email += 100;
        }
        else if (user_info.email[i] == '.')
        {
            check_email++;
        }
    }
    for (int i = 0; i < 20; i++)
    {
        if ((user_info.pass[i] >= 'A' && user_info.pass[i] <= 'Z') || (user_info.pass[i] >= 'a' && user_info.pass[i] <= 'z'))
        {
            check_pass_letter++;
            check_pass_length++;
        }
        else if (user_info.pass[i] >= '0' && user_info.pass[i] <= '9')
        {
            check_pass_length++;
            check_pass_num++;
        }
        else
        {
            check_pass_length++;
            check_pass_special++;
        }
    }
    for (int i = 0; i < 20; i++)
    {
        if (user_info.pass[i] == user_info.cpass[i])
        {
            continue;
        }
        else
        {
            check_cpass++;
        }
    }
    int check = 0;

    if (check_email == 101 && check_pass_letter > 0 && check_pass_num > 0 && check_pass_special > 0 && check_cpass == 0 && check_pass_length >= 6)
    {

        while (fgets(line, sizeof(line), users_file) != NULL)
        {

            line[strcspn(line, "\n")] = 0;

            if (strcmp(line, user_info.email) == 0)
            {
                printf("Email already exists!\n");
                check = 1;
                regester();
                break;
            }
        }
        if (check == 0)
        {
            fclose(users_file);
            fopen("users_info.csv", "a");
            fprintf(users_file, "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
            fprintf(users_file, user_info.email);
            fprintf(users_file, "\n");
            fprintf(users_file, user_info.pass);
            fprintf(users_file, "\n");
            fprintf(users_file, "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
            fclose(users_file);
            clear_console();
            printf("Regester Succesfully!\n");
            admin_other_choices();
        }
    }
    else
    {
        clear_console();
        printf("Please! Write a TRUE email & password\n");
        regester();
    }
    return 0;
}
int agent_regester()
{
    clear_console();
    struct user_regester
    {
        char email[150];
        char pass[20];
        char cpass[20];
    };
    struct user_regester user_info = {'0', '0', '0'};
    printf("///////////////////////////// The rules of writing a TRUE email & password /////////////////////////////\nFor Email!\n[1] Email must contain '@' and '.'\nExample(email@gmail.com)\nFor Password!\n[1] The password must contain at least 1 special character\n[2] The password must contain at least 1 number\n[3] The Password must include normal characters\n[4] The length of the password at least 6 characters\n");
    printf("Enter your email: ");
    scanf("%s", &user_info.email);
    printf("Enter your password: ");
    scanf("%s", &user_info.pass);
    printf("Confirm your password: ");
    scanf("%s", &user_info.cpass);
    FILE *users_file;
    users_file = fopen("agent_info.csv", "r");
    char fileinfo[1000000];
    fgets(fileinfo, 1000000, users_file);
    char line[MAX_LINE_LENGTH];
    int check_email = 0;
    int check_pass_letter = 0;
    int check_pass_num = 0;
    int check_pass_length = 0;
    int check_pass_special = 0;
    int check_cpass = 0;
    for (int i = 0; i < 150; i++)
    {
        if (user_info.email[i] == '@')
        {
            check_email += 100;
        }
        else if (user_info.email[i] == '.')
        {
            check_email++;
        }
    }
    for (int i = 0; i < 20; i++)
    {
        if ((user_info.pass[i] >= 'A' && user_info.pass[i] <= 'Z') || (user_info.pass[i] >= 'a' && user_info.pass[i] <= 'z'))
        {
            check_pass_letter++;
            check_pass_length++;
        }
        else if (user_info.pass[i] >= '0' && user_info.pass[i] <= '9')
        {
            check_pass_length++;
            check_pass_num++;
        }
        else
        {
            check_pass_length++;
            check_pass_special++;
        }
    }
    for (int i = 0; i < 20; i++)
    {
        if (user_info.pass[i] == user_info.cpass[i])
        {
            continue;
        }
        else
        {
            check_cpass++;
        }
    }
    int check = 0;

    if (check_email == 101 && check_pass_letter > 0 && check_pass_num > 0 && check_pass_special > 0 && check_cpass == 0 && check_pass_length >= 6)
    {

        while (fgets(line, sizeof(line), users_file) != NULL)
        {

            line[strcspn(line, "\n")] = 0;

            if (strcmp(line, user_info.email) == 0)
            {
                printf("Email already exists!\nLogin! \n");
                check = 1;
                admin_other_choices();
                break;
            }
        }
        if (check == 0)
        {
            fclose(users_file);
            fopen("agent_info.csv", "a");
            fprintf(users_file, "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
            fprintf(users_file, user_info.email);
            fprintf(users_file, "\n");
            fprintf(users_file, user_info.pass);
            fprintf(users_file, "\n");
            fprintf(users_file, "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
            fclose(users_file);
            clear_console();
            printf("Regester Succesfully!\nLogin: \n");
            agent_login();
        }
    }
    else
    {
        clear_console();
        printf("Please! Write a TRUE email & password\n");
        agent_regester();
    }
    return 0;
}


struct Claim {
    char customer_email[100];
    char claim[1000];
    char agent_reply[1000];
};


void add_claim_to_csv(struct Claim new_claim) {
    FILE *file = fopen("claims.csv", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s,%s,%s\n", new_claim.customer_email, new_claim.claim, new_claim.agent_reply);
    fclose(file);
}


void read_claims_from_csv(struct Claim claims[], int *num_claims) {
    FILE *file = fopen("claims.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    *num_claims = 0;
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", claims[*num_claims].customer_email,
                  claims[*num_claims].claim, claims[*num_claims].agent_reply) != EOF) {
        (*num_claims)++;
    }
    fclose(file);
}


void show_all_claims() {
    struct Claim claims[100];
    int num_claims;

    read_claims_from_csv(claims, &num_claims);

    if (num_claims == 0) {
        printf("No claims to display.\n");
    } else {
        printf("All Claims:\n");
        for (int i = 0; i < num_claims; i++) {
            printf("Claim %d:\n", i + 1);
            printf("Customer Email: %s\n", claims[i].customer_email);
            printf("Claim: %s\n", claims[i].claim);
            if (strlen(claims[i].agent_reply) > 0) {
                printf("Agent Reply: %s\n", claims[i].agent_reply);
            } else {
                printf("Agent has not replied to this claim yet.\n");

            }
            printf("\n");
        }
    }
}


void reply_to_claim_for_customer_by_email() {
    struct Claim claims[100];
    int num_claims;

    read_claims_from_csv(claims, &num_claims);

    char customer_email_to_reply[100];
    printf("Enter customer email to reply to their claim: ");
    scanf("%s", customer_email_to_reply);

    int i;
    for (i = 0; i < num_claims; i++) {
        if (strcmp(claims[i].customer_email, customer_email_to_reply) == 0) {
            printf("Claim found:\n");
            printf("Claim: %s\n", claims[i].claim);

            printf("Enter agent reply: ");
            scanf(" %[^\n]s", claims[i].agent_reply);
                FILE*replies=fopen("replies.csv","a+");
                fprintf(replies,"%s",claims[i].agent_reply);
            add_claim_to_csv(claims[i]);
            printf("Agent reply recorded successfully.\n");
            fclose(replies);
            break;
        }
    }

    if (i == num_claims) {
        printf("Claim not found for the provided customer email.\n");
    }

}


void make_claim_for_customer() {
    struct Claim new_claim;

    printf("Enter your email: ");
    scanf("%s", new_claim.customer_email);

    printf("Enter your claim: ");
    scanf(" %[^\n]s", new_claim.claim);

    strcpy(new_claim.agent_reply, "");

    add_claim_to_csv(new_claim);
    printf("Claim recorded successfully.\n");


}
void show_reply_from_agent_to_customer(char *customer_email) {
    FILE *replies = fopen("replies.csv", "r");
    if (replies == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Customer Email\tAgent Reply\n");
    printf("------------------------------------\n");

    char line[1000];
    while (fgets(line, sizeof(line), replies) != NULL) {
        char *customer_email = strtok(line, ",");
        char *agent_reply = strtok(NULL, "\n");

        printf("%s\t%s\n", customer_email, agent_reply);
    }

    fclose(replies);
}


void login(){
    while (1)
    {
        if (login_succes == 0)
        {
            printf("Choose your account type :\n");
            printf("1. admin\n");
            printf("2. agent\n");
            printf("3. customer\n");
            int login_choice;
            scanf("%d", &login_choice);
            if (login_choice == 1)
            {
                printf("Admin login!\n");
                admin_login();
            }
            else if (login_choice == 2)
            {
                printf("Agent login!\n");
                agent_login();
            }
            else if (login_choice == 3)
            {
                user_login();
            }
        }
        else if (login_succes == 1)
        {
            admin_other_choices();
        }
        else if (login_succes == 2)
        {
            agent_other_choices();
        }
        else if (login_succes == 3)
        {
            user_other_choices();
        }
    }
}
int user_other_choices() {
    while(1) {
        printf("1. Your policy\n");
        printf("2. Report a complaint\n");
        printf("3. Show replay\n ");
        printf("4. Exit\n");
        int action;
        scanf("%d", &action);
        switch(action) {
            case 1:
                printf("Enter the customer email: ");
                scanf("%s", customer_email);
                display_policies(customer_email);
                break;
            case 2:
                make_claim_for_customer();
                break;

            case 3:
              show_reply_from_agent_to_customer(customer_email);
              break;
            case 4:
                exit (0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}
int agent_other_choices() {
    while(1) {
        printf("1. Create policy\n");
        printf("2. Display policy\n");
        printf("3. Edit Policy\n");
        printf("4. Show all complaints\n");
        printf("5. Reply Claims \n");
        printf("6. Exit \n");
        int action;
        scanf("%d", &action);
        switch(action) {
            case 1:
                create_policy();
                break;
            case 2:
                view_policies();
                user_login();
                display_policies(customer_email);
                break;
            case 3:
                edit_policy();
                break;
            case 4:
                show_all_claims();
                break;
            case 5:
                reply_to_claim_for_customer_by_email();
               break;
            case 6:
                exit (0);

            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}
int admin_other_choices()
{
    while(1){
    printf("1. Create customer account\n");
    printf("2. Create agent account\n");
    printf("3. Back to main menu\n");
    int action;
    scanf("%d", &action);
    if (action == 1)
    {
        regester();
    }
    else if (action == 2)
    {
        agent_regester();
    }
    else if (action == 3)
    {

    exit (0);
    }
}}
int main()
{
    login();
    return 0;
}
