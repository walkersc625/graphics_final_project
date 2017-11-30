
#include <string>

bool not_valid_arg(char *arg);
void display_arg_list();


bool parse_args(char *arg, char *buffer)
{
	if (not_valid_arg(arg)) {
		display_arg_list();
		return false;
	}

	strcpy(buffer, "../assets/");
	strcat(buffer, arg);
	strcat(buffer, ".jpg");
	return true;
}

bool not_valid_arg(char *arg)
{
	return false;
}

void display_arg_list()
{
	return;
}