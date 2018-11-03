#ifndef TEST_H
#define TEST_H
#ifdef __cplusplus
extern "C"
{
#endif
int connectMysql();
int isAccountValid(char *account,char *passwd);
int setLoginStatus(const char *account,int flag);
void disconnectMysql();
int c_register(const char *account,const char *password,const char *nickname,char sex);
int memorize_word_data_input(char *user_id,char *str_num,char *output_file,char *error_info);
int get_num_per_day(char *user_id,char *error_info);
int record_footstep(char *user_id,char num_per_day,char *error_info);
int c_set_plan(char *str_account,int num_per_day_int);
int c_get_record(char *str_user_id,int *total,int *remain);
int c_add_my_word(char *str_user_id,char *word_id,char *word);
int c_select_word_notebook(char *user_id,int *num,char *outfile);
int c_get_word_def(char *word_id,char *def);
int c_delete_my_word_from_note(char *word_id);
#ifdef __cplusplus
}
#endif
#endif
