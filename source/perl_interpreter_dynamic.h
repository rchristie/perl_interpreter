/* Used by dynamic_versions.h */
struct Interpreter_library_strings {   char *version; char *archname; char *base64_string; };
#include "dynamic_versions.h"

#define LOAD_FUNCTION(symbol) \
			if (return_code && (!(symbol ## handle = dlsym(interpreter_handle, "__" #symbol )))) \
			{ \
				 (*display_message_function)(ERROR_MESSAGE,"Unable to find symbol %s", "__" #symbol ); \
				 return_code = 0; \
			}

static int use_dynamic_interpreter = 0;

void (*create_interpreter_handle)(int argc, char **argv, const char *initial_comfile,
	 int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __create_interpreter_(int argc, char **argv, const char *initial_comfile,
	 int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __create_interpreter_(argc, argv, initial_comfile, status)
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*interpreter_destroy_string_handle)(char *string);
#if ! defined (NO_STATIC_FALLBACK)
void __interpreter_destroy_string_(char *string);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __interpreter_destroy_string_(string)
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*destroy_interpreter_handle)(int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __destroy_interpreter_(int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __destroy_interpreter_(status)
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*redirect_interpreter_output_handle)(int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __redirect_interpreter_output_(int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __redirect_interpreter_output_(status)
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*interpreter_set_display_message_function_handle)
	  (Interpreter_display_message_function *function, int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __interpreter_set_display_message_function_(Interpreter_display_message_function *function,
	int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __interpreter_set_display_message_function_(function, status)
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*interpret_command_handle)(char *command_string, void *user_data, int *quit,
	 execute_command_function_type execute_command_function, int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __interpret_command_(char *command_string, void *user_data, int *quit,
	 execute_command_function_type execute_command_function, int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __interpret_command_(command_string, user_data, quit, execute_command_function, status)
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*interpreter_evaluate_integer_handle)(char *expression, int *result, int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __interpreter_evaluate_integer_(char *expression, int *result, int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __interpreter_evaluate_integer_(expression, result, status);
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*interpreter_set_integer_handle)(char *variable_name, int *value, int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __interpreter_set_integer_(char *variable_name, int *value, int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __interpreter_set_integer_(variable_name, value, status);
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*interpreter_evaluate_double_handle)(char *expression, double *result, int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __interpreter_evaluate_double_(char *expression, double *result, int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __interpreter_evaluate_double_(expression, result, status);
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*interpreter_set_double_handle)(char *variable_name, double *value, int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __interpreter_set_double_(char *variable_name, double *value, int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __interpreter_set_double_(variable_name, value, status);
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*interpreter_evaluate_string_handle)(char *expression, char **result, int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __interpreter_evaluate_string_(char *expression, char **result, int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __interpreter_evaluate_string_(expression, result, status);
#endif /* ! defined (NO_STATIC_FALLBACK) */

void (*interpreter_set_string_handle)(char *variable_name, char *value, int *status);
#if ! defined (NO_STATIC_FALLBACK)
void __interpreter_set_string_(char *variable_name, char *value, int *status);
#else /* ! defined (NO_STATIC_FALLBACK) */
#define __interpreter_set_string_(variable_name, value, status);
#endif /* ! defined (NO_STATIC_FALLBACK) */

void interpret_command_(char *command_string, void *user_data, int *quit,
  execute_command_function_type execute_command_function, int *status)
/*******************************************************************************
LAST MODIFIED : 19 May 2000

DESCRIPTION:
Takes a <command_string>, processes this through the Perl interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*interpret_command_handle)(command_string, user_data, quit,
			execute_command_function, status);
	}
	else
	{
		__interpret_command_(command_string, user_data, quit,
			execute_command_function, status);
	}
} /* interpret_command */

#if __GLIBC__ >= 2
#include <gnu/libc-version.h>
#endif
#if defined (BYTE_ORDER)
#if (1234==BYTE_ORDER)
static int glibc_version_greater_than_2_2_4(void)
/*******************************************************************************
LAST MODIFIED : 26 November 2002

DESCRIPTION :
Need to read the glibc version so that we can determine if we need to 
swap the endianness of values going into a64l
==============================================================================*/
{
#if __GLIBC__ >= 2
	char *version_string;
	int major_version, minor_version, minor_sub_version;
#endif /* __GLIBC__ >= 2 */
	static int return_code = -1;

	/* This gets called a lot so lets make it fast */
	if (return_code == -1)
	{
#if __GLIBC__ >= 2
		version_string = (char *)gnu_get_libc_version();
		if (sscanf(version_string, "%d.%d.%d", &major_version, &minor_version, 
			&minor_sub_version))
		{
			
			if ((major_version > 2) ||
				((major_version == 2) && (minor_version > 2)) ||
				((major_version == 2) && (minor_version == 2) && (minor_sub_version > 4)))
			{
				return_code = 1;
			}
			else
			{
				return_code = 0;
			}
		}
		else
		{
			return_code = 0;
		}
#else /* __GLIBC__ >= 2 */
		return_code = 0;
#endif/* __GLIBC__ >= 2 */
	}
	return (return_code);
} /* get_glibc_version */
#endif /* (1234==BYTE_ORDER) */
#endif /* defined (BYTE_ORDER) */

static char *write_base64_string_to_binary_file(char *base64_string)
/*******************************************************************************
LAST MODIFIED : 28 March 2003

DESCRIPTION :
This wrapper allows the passing of the <base64_string> which is intended to
contain a binary file converted to base64.  This function converts it back to
binary and writes a temporary file for which the filename is returned.
It is up to the calling routine to free the string returned and to
remove the temporary file it refers to.
==============================================================================*/
{
	char *ptr_temp_uid_name,*return_string,temp_uid_name[L_tmpnam],*total_uid;
	FILE *uid_file;
	int i,j,string_length;
	long uid_long_data;

	if (base64_string)
	{
		string_length=strlen(base64_string);
		if (tmpnam(temp_uid_name) && (uid_file=fopen(temp_uid_name, "w"))
			&& (total_uid = (char *)malloc(string_length+1))
			&& (return_string = (char *)malloc(strlen(temp_uid_name)+1)))
		{
			j=0;
			for (i=0;i<string_length-1;i+=6)
			{
#if defined (BYTE_ORDER)
#if (1234==BYTE_ORDER)
				if (glibc_version_greater_than_2_2_4())
				{
					/* Don't need to swap now */
					uid_long_data=a64l(base64_string + i);
				}
				else
				{
					char tmp_string[6];
					tmp_string[0]=base64_string[i + 5];
					tmp_string[1]=base64_string[i + 4];
					tmp_string[2]=base64_string[i + 3];
					tmp_string[3]=base64_string[i + 2];
					tmp_string[4]=base64_string[i + 1];
					tmp_string[5]=base64_string[i];
					uid_long_data=a64l(tmp_string);
				}
#else /* (1234==BYTE_ORDER) */
				uid_long_data=a64l(base64_string + i);
#endif /* (1234==BYTE_ORDER) */
#else /* defined (BYTE_ORDER) */
				uid_long_data=a64l(base64_string + i);
#endif /* defined (BYTE_ORDER) */
				total_uid[j]=(char)(255 & uid_long_data);
				j++;
				total_uid[j]=(char)(255 & (uid_long_data >> 8));
				j++;
				total_uid[j]=(char)(255 & (uid_long_data >> 16));
				j++;
				total_uid[j]=(char)(255 & (uid_long_data >> 24));
				j++;
			}
			fwrite(total_uid,1,4*string_length/6,uid_file);
			free(total_uid);
			fclose(uid_file);
			strcpy(return_string, temp_uid_name);
		}
		else
		{
			display_message(ERROR_MESSAGE,
				"write_base64_string_to_binary_file.  Invalid argument(s)");
			return_string = (char *)NULL;
		}
	}
	else
	{
		display_message(ERROR_MESSAGE,
			"write_base64_string_to_binary_file.  Invalid argument(s)");
		return_string = (char *)NULL;
	}

	return (return_string);
} /* write_base64_string_to_binary_file */

void create_interpreter_ (int argc, char **argv, const char *initial_comfile,
	int *status)
/*******************************************************************************
LAST MODIFIED : 28 March 2003

DESCRIPTION:
Creates the interpreter for processing commands.
==============================================================================*/
{
	char command[300], *library, perl_archname[200], *perl_executable,
		*perl_executable_default = "perl", *perl_interpreter_string, perl_version[200],
		perl_archlib[200], perl_shared_library[200];
	FILE *perl_result;
	int i, number_of_perl_interpreters, return_code, stdout_pipe[2], old_stdout;
	void *interpreter_handle, *perl_handle;

	return_code = 0;
	use_dynamic_interpreter = 0;
	perl_interpreter_string = (char *)NULL;

	number_of_perl_interpreters = sizeof(interpreter_strings) /
		sizeof(struct Interpreter_library_strings);
	if (number_of_perl_interpreters)
	{
		if (0 == pipe(stdout_pipe))
		{
			/* Redirect stdout */
			old_stdout = dup(STDOUT_FILENO);
			dup2(stdout_pipe[1], STDOUT_FILENO);

			/* We are only expecting a little bit of stuff so I am
				hoping that the pipe can buffer it */
			if (!(perl_executable = getenv("CMISS" ABI_ENV "_PERL")))
			{
				if (!(perl_executable = getenv("CMISS_PERL")))
				{
					perl_executable = perl_executable_default;
				}
			}

			sprintf(command, "%s -MConfig -e 'print \"$Config{archname} $Config{version} $Config{archlibexp}\n\"'", perl_executable);
			system(command);

			/* Set stdout back */
			dup2(old_stdout, STDOUT_FILENO);

			if (perl_result = fdopen(stdout_pipe[0], "r"))
			{
				if (3 == fscanf(perl_result, "%190s %190s %190s", perl_archname, 
					perl_version, perl_archlib))
				{
					for (i = 0 ; i < number_of_perl_interpreters ; i++)
					{
						if ((!strcmp(perl_archname, interpreter_strings[i].archname))
							&& (!strcmp(perl_version, interpreter_strings[i].version)))
						{
							perl_interpreter_string = interpreter_strings[i].base64_string;
						}
					}
				}
				else
				{
					display_message(ERROR_MESSAGE,"create_interpreter.  "
						"Problem executing \"%s\"", command);
				}
			}
		}
	}

	if (perl_interpreter_string)
	{
		if (library = write_base64_string_to_binary_file(perl_interpreter_string))
		{
			sprintf(perl_shared_library, "%s/CORE/libperl.so", perl_archlib);
			if (perl_handle = dlopen(perl_shared_library, RTLD_LAZY | RTLD_GLOBAL))
			{
				if (interpreter_handle = dlopen(library, RTLD_LAZY))
				{
					return_code = 1;
				}
				else
				{
					dlclose(perl_handle);
				}
			}
			/* Hopefully we can remove the file already and if the OS still
				wants it, it will just keep a handle */
			remove(library);
			free(library);
		}
	}

	if (!return_code)
	{
		display_message(ERROR_MESSAGE,"create_interpreter.  "
			"Unable to open a dynamic perl_interpreter.  Using the internal one. %s",
			dlerror()) ;
	}

	if (return_code)
	{
		LOAD_FUNCTION(create_interpreter_);
		if (return_code)
		{
			(*create_interpreter_handle)(argc, argv, initial_comfile, status);
			return_code = *status;
		}
		LOAD_FUNCTION(interpreter_destroy_string_);
		LOAD_FUNCTION(destroy_interpreter_);
		LOAD_FUNCTION(redirect_interpreter_output_);
		LOAD_FUNCTION(interpreter_set_display_message_function_);
		LOAD_FUNCTION(interpret_command_);
		LOAD_FUNCTION(interpreter_evaluate_integer_);
		LOAD_FUNCTION(interpreter_set_integer_);
		LOAD_FUNCTION(interpreter_evaluate_double_);
		LOAD_FUNCTION(interpreter_set_double_);
		LOAD_FUNCTION(interpreter_evaluate_string_);
		LOAD_FUNCTION(interpreter_set_string_);
	}
	if (return_code)
	{
		/* All the functions should be valid if the return_code
			is still 1 */
		use_dynamic_interpreter = 1;
	}
	else
	{
#if ! defined (NO_STATIC_FALLBACK)
		__create_interpreter_(argc, argv, initial_comfile, status);
		return_code = *status;
#else /* ! defined (NO_STATIC_FALLBACK) */
		display_message(ERROR_MESSAGE,"create_interpreter.  "
			"No fallback static perl interpreter was included in this "
			"executable.");
		return_code = 0;
#endif /* ! defined (NO_STATIC_FALLBACK) */
	}
	*status = return_code;
}

void destroy_interpreter_(int *status)
/*******************************************************************************
LAST MODIFIED : 24 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*destroy_interpreter_handle)(status);
	}
	else
	{
		__destroy_interpreter_(status);
	}
} /* destroy_interpreter */

void interpreter_set_display_message_function_(Interpreter_display_message_function *function,
	int *status)
/*******************************************************************************
LAST MODIFIED : 26 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*interpreter_set_display_message_function_handle)(function, status);
	}
	else
	{
		__interpreter_set_display_message_function_(function, status);
	}
} /* redirect_interpreter_output */

void redirect_interpreter_output_(int *status)
/*******************************************************************************
LAST MODIFIED : 24 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*redirect_interpreter_output_handle)(status);
	}
	else
	{
		__redirect_interpreter_output_(status);
	}
} /* redirect_interpreter_output */

void interpreter_evaluate_integer_(char *expression, int *result, int *status)
/*******************************************************************************
LAST MODIFIED : 24 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*interpreter_evaluate_integer_handle)(expression, result, status);
	}
	else
	{
		__interpreter_evaluate_integer_(expression, result, status);
	}
} /* interpreter_evaluate_integer */

void interpreter_set_integer_(char *variable_name, int *value, int *status)
/*******************************************************************************
LAST MODIFIED : 24 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*interpreter_set_integer_handle)(variable_name, value, status);
	}
	else
	{
		__interpreter_set_integer_(variable_name, value, status);
	}
} /* interpreter_set_integer */

void interpreter_evaluate_double_(char *expression, double *result, int *status)
/*******************************************************************************
LAST MODIFIED : 24 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*interpreter_evaluate_double_handle)(expression, result, status);
	}
	else
	{
		__interpreter_evaluate_double_(expression, result, status);
	}
} /* interpreter_evaluate_double */

void interpreter_set_double_(char *variable_name, double *value, int *status)
/*******************************************************************************
LAST MODIFIED : 24 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*interpreter_set_double_handle)(variable_name, value, status);
	}
	else
	{
		__interpreter_set_double_(variable_name, value, status);
	}
} /* interpreter_set_double */

void interpreter_evaluate_string_(char *expression, char **result, int *status)
/*******************************************************************************
LAST MODIFIED : 24 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*interpreter_evaluate_string_handle)(expression, result, status);
	}
	else
	{
		__interpreter_evaluate_string_(expression, result, status);
	}
} /* interpreter_evaluate_string */

void interpreter_destroy_string_(char *string)
/*******************************************************************************
LAST MODIFIED : 24 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*interpreter_destroy_string_handle)(string);
	}
	else
	{
		__interpreter_destroy_string_(string);
	}
} /* interpreter_destroy_string */

void interpreter_set_string_(char *variable_name, char *value, int *status)
/*******************************************************************************
LAST MODIFIED : 24 March 2003

DESCRIPTION :
Frees the memory associated with a string allocated by the interpreter.
==============================================================================*/
{
	if (use_dynamic_interpreter)
	{
		(*interpreter_set_string_handle)(variable_name, value, status);
	}
	else
	{
		__interpreter_set_string_(variable_name, value, status);
	}
} /* interpreter_set_string */
