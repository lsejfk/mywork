
int connectMysql();
int isAccountValid(char *account,char *passwd);
int memorize_word_data_input(char *user_id,char *str_num,char *output_file,char *error_info);
int get_num_per_day(char *user_id,char *error_info);

int record_footstep(char *user_id,int num_per_day,char *error_info);
int c_get_record(char *str_user_id,int *total,int *remain);
int c_select_word_notebook(char *user_id,char *out_file);
