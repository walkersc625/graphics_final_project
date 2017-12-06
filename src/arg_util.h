#include <string>
#include <iostream>

using namespace std;

bool not_valid_arg(char *arg);
void display_arg_list();


bool parse_args(char *arg, char* flag, char *buffer)
{
	if (not_valid_arg(arg)) {
		printf("ERROR: Invalid texture name\n");
		display_arg_list();
		return false;
	}

	if (flag != NULL) {
		if (!strcmp(flag, "-s")) {
			strcpy(buffer, "../assets/tiny/");
		}
	} else {
		strcpy(buffer, "../assets/");
	}

	strcat(buffer, arg);
	strcat(buffer, ".jpg");
	return true;
}

bool not_valid_arg(char *arg)
{
	return (strcmp(arg, "aqua_starburst"))
	    && (strcmp(arg, "blue_lines"))
	    && (strcmp(arg, "burlap"))
	    && (strcmp(arg, "cactus"))
	    && (strcmp(arg, "damask"))
	    && (strcmp(arg, "diagonals"))
	    && (strcmp(arg, "farfalle"))
	    && (strcmp(arg, "fur"))
	    && (strcmp(arg, "green_cells"))
	    && (strcmp(arg, "gray_cells"))
	    && (strcmp(arg, "leather"))
	    && (strcmp(arg, "noodles"))
	    && (strcmp(arg, "rock"))
	    && (strcmp(arg, "vintage"))
	    && (strcmp(arg, "white_lines"));
}

void display_arg_list()
{
	cout << "Available textures: \n"
	     << "\taqua_starburst\n"
	     << "\tblue_lines\n"
	     << "\tburlap\n"
	     << "\tcactus\n"
	     << "\tdamask\n"
	     << "\tdiagonals\n"
	     << "\tfarfalle\n"
	     << "\tfur\n"
	     << "\tgray_cells\n"
	     << "\tleather\n"
	     << "\tnoodles\n"
	     << "\trock\n"
	     << "\tvintage\n"
	     << "\twhite_lines\n";
}