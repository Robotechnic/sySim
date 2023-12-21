/*
  File autogenerated by gengetopt version 2.23
  generated with the following command:
  /usr/bin/gengetopt --conf-parser --input=/home/robotechnic/Documents/c++ projet/sySim/src/sySim.ggo --file-name=argparse --output-dir=/home/robotechnic/Documents/c++ projet/sySim/src/argparse 

  The developers of gengetopt consider the fixed text that goes in all
  gengetopt output files to be in the public domain:
  we make no copyright claims on it.
*/

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FIX_UNUSED
#define FIX_UNUSED(X) (void) (X) /* avoid warnings for unused params */
#endif

#include <getopt.h>

#include "argparse.h"

const char *gengetopt_args_info_purpose = "Simulate a simple symmetric communication channel";

const char *gengetopt_args_info_usage = "Usage: sySim [OPTION]...";

const char *gengetopt_args_info_versiontext = "";

const char *gengetopt_args_info_description = "This program simulates a communication channel between two programs.\nIt allows to test communication protocols and simulate packet loss and\ncorruption.";

const char *gengetopt_args_info_help[] = {
  "  -h, --help                Print help and exit",
  "  -V, --version             Print version and exit",
  "\nSimulation parameters:",
  "  -m, --messages=INT        Number of messages to send  (default=`10')",
  "  -l, --loss=FLOAT          Packet loss probability  (default=`0.0')",
  "  -c, --corruption=FLOAT    Packet corruption probability  (default=`0.0')",
  "  -d, --delay=FLOAT         Average delay between packets  (default=`5.0')",
  "  -t, --maxTime=FLOAT       Maximum time to run the simulation\n                              (default=`200.0')",
  "  -s, --seed=INT            Seed for the random number generator\n                              (default=`42')",
  "  -b, --bidirectional       If set, the channel will be bidirectional\n                              (default=off)",
  "\nLogging parameters:",
  "  -L, --loglevel=INT        Logging level  (default=`2')",
  "      --logfile=filename    If set, the logging will also be written to this\n                              file",
  "  -q, --quiet               If set, the program won't print anything to stdout\n                              (default=off)",
  "  -k, --color               If set, the program will use colors in the output\n                              (default=off)",
  "\nMessage checking:",
  "      --check               If set, the simulator will check that the payloads\n                              are received in the correct order  (default=off)",
  "  -f, --stop-on-failure     If set, the simulator will continue even if the\n                              messages are not received in the correct order\n                              (default=off)",
  "\nVisualization:",
  "  -v, --visualize=filename  If set, the simulator will export an svg file with\n                              the visualization of the simulation",
  "\nConfiguration file:",
  "  -C, --conf-file=filename  If set, the simulator will read the configuration\n                              from this file",
    0
};

typedef enum {ARG_NO
  , ARG_FLAG
  , ARG_STRING
  , ARG_INT
  , ARG_FLOAT
} cmdline_parser_arg_type;

static
void clear_given (struct gengetopt_args_info *args_info);
static
void clear_args (struct gengetopt_args_info *args_info);

static int
cmdline_parser_internal (int argc, char **argv, struct gengetopt_args_info *args_info,
                        struct cmdline_parser_params *params, const char *additional_error);

struct line_list
{
  char * string_arg;
  struct line_list * next;
};

static struct line_list *cmd_line_list = 0;
static struct line_list *cmd_line_list_tmp = 0;

static void
free_cmd_list(void)
{
  /* free the list of a previous call */
  if (cmd_line_list)
    {
      while (cmd_line_list) {
        cmd_line_list_tmp = cmd_line_list;
        cmd_line_list = cmd_line_list->next;
        free (cmd_line_list_tmp->string_arg);
        free (cmd_line_list_tmp);
      }
    }
}


static char *
gengetopt_strdup (const char *s);

static
void clear_given (struct gengetopt_args_info *args_info)
{
  args_info->help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->messages_given = 0 ;
  args_info->loss_given = 0 ;
  args_info->corruption_given = 0 ;
  args_info->delay_given = 0 ;
  args_info->maxTime_given = 0 ;
  args_info->seed_given = 0 ;
  args_info->bidirectional_given = 0 ;
  args_info->loglevel_given = 0 ;
  args_info->logfile_given = 0 ;
  args_info->quiet_given = 0 ;
  args_info->color_given = 0 ;
  args_info->check_given = 0 ;
  args_info->stop_on_failure_given = 0 ;
  args_info->visualize_given = 0 ;
  args_info->conf_file_given = 0 ;
}

static
void clear_args (struct gengetopt_args_info *args_info)
{
  FIX_UNUSED (args_info);
  args_info->messages_arg = 10;
  args_info->messages_orig = NULL;
  args_info->loss_arg = 0.0;
  args_info->loss_orig = NULL;
  args_info->corruption_arg = 0.0;
  args_info->corruption_orig = NULL;
  args_info->delay_arg = 5.0;
  args_info->delay_orig = NULL;
  args_info->maxTime_arg = 200.0;
  args_info->maxTime_orig = NULL;
  args_info->seed_arg = 42;
  args_info->seed_orig = NULL;
  args_info->bidirectional_flag = 0;
  args_info->loglevel_arg = 2;
  args_info->loglevel_orig = NULL;
  args_info->logfile_arg = NULL;
  args_info->logfile_orig = NULL;
  args_info->quiet_flag = 0;
  args_info->color_flag = 0;
  args_info->check_flag = 0;
  args_info->stop_on_failure_flag = 0;
  args_info->visualize_arg = NULL;
  args_info->visualize_orig = NULL;
  args_info->conf_file_arg = NULL;
  args_info->conf_file_orig = NULL;
  
}

static
void init_args_info(struct gengetopt_args_info *args_info)
{


  args_info->help_help = gengetopt_args_info_help[0] ;
  args_info->version_help = gengetopt_args_info_help[1] ;
  args_info->messages_help = gengetopt_args_info_help[3] ;
  args_info->loss_help = gengetopt_args_info_help[4] ;
  args_info->corruption_help = gengetopt_args_info_help[5] ;
  args_info->delay_help = gengetopt_args_info_help[6] ;
  args_info->maxTime_help = gengetopt_args_info_help[7] ;
  args_info->seed_help = gengetopt_args_info_help[8] ;
  args_info->bidirectional_help = gengetopt_args_info_help[9] ;
  args_info->loglevel_help = gengetopt_args_info_help[11] ;
  args_info->logfile_help = gengetopt_args_info_help[12] ;
  args_info->quiet_help = gengetopt_args_info_help[13] ;
  args_info->color_help = gengetopt_args_info_help[14] ;
  args_info->check_help = gengetopt_args_info_help[16] ;
  args_info->stop_on_failure_help = gengetopt_args_info_help[17] ;
  args_info->visualize_help = gengetopt_args_info_help[19] ;
  args_info->conf_file_help = gengetopt_args_info_help[21] ;
  
}

void
cmdline_parser_print_version (void)
{
  printf ("%s %s\n",
     (strlen(CMDLINE_PARSER_PACKAGE_NAME) ? CMDLINE_PARSER_PACKAGE_NAME : CMDLINE_PARSER_PACKAGE),
     CMDLINE_PARSER_VERSION);

  if (strlen(gengetopt_args_info_versiontext) > 0)
    printf("\n%s\n", gengetopt_args_info_versiontext);
}

static void print_help_common(void)
{
	size_t len_purpose = strlen(gengetopt_args_info_purpose);
	size_t len_usage = strlen(gengetopt_args_info_usage);

	if (len_usage > 0) {
		printf("%s\n", gengetopt_args_info_usage);
	}
	if (len_purpose > 0) {
		printf("%s\n", gengetopt_args_info_purpose);
	}

	if (len_usage || len_purpose) {
		printf("\n");
	}

	if (strlen(gengetopt_args_info_description) > 0) {
		printf("%s\n\n", gengetopt_args_info_description);
	}
}

void
cmdline_parser_print_help (void)
{
  int i = 0;
  print_help_common();
  while (gengetopt_args_info_help[i])
    printf("%s\n", gengetopt_args_info_help[i++]);
}

void
cmdline_parser_init (struct gengetopt_args_info *args_info)
{
  clear_given (args_info);
  clear_args (args_info);
  init_args_info (args_info);
}

void
cmdline_parser_params_init(struct cmdline_parser_params *params)
{
  if (params)
    { 
      params->override = 0;
      params->initialize = 1;
      params->check_required = 1;
      params->check_ambiguity = 0;
      params->print_errors = 1;
    }
}

struct cmdline_parser_params *
cmdline_parser_params_create(void)
{
  struct cmdline_parser_params *params = 
    (struct cmdline_parser_params *)malloc(sizeof(struct cmdline_parser_params));
  cmdline_parser_params_init(params);  
  return params;
}

static void
free_string_field (char **s)
{
  if (*s)
    {
      free (*s);
      *s = 0;
    }
}


static void
cmdline_parser_release (struct gengetopt_args_info *args_info)
{

  free_string_field (&(args_info->messages_orig));
  free_string_field (&(args_info->loss_orig));
  free_string_field (&(args_info->corruption_orig));
  free_string_field (&(args_info->delay_orig));
  free_string_field (&(args_info->maxTime_orig));
  free_string_field (&(args_info->seed_orig));
  free_string_field (&(args_info->loglevel_orig));
  free_string_field (&(args_info->logfile_arg));
  free_string_field (&(args_info->logfile_orig));
  free_string_field (&(args_info->visualize_arg));
  free_string_field (&(args_info->visualize_orig));
  free_string_field (&(args_info->conf_file_arg));
  free_string_field (&(args_info->conf_file_orig));
  
  

  clear_given (args_info);
}


static void
write_into_file(FILE *outfile, const char *opt, const char *arg, const char *values[])
{
  FIX_UNUSED (values);
  if (arg) {
    fprintf(outfile, "%s=\"%s\"\n", opt, arg);
  } else {
    fprintf(outfile, "%s\n", opt);
  }
}


int
cmdline_parser_dump(FILE *outfile, struct gengetopt_args_info *args_info)
{
  int i = 0;

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot dump options to stream\n", CMDLINE_PARSER_PACKAGE);
      return EXIT_FAILURE;
    }

  if (args_info->help_given)
    write_into_file(outfile, "help", 0, 0 );
  if (args_info->version_given)
    write_into_file(outfile, "version", 0, 0 );
  if (args_info->messages_given)
    write_into_file(outfile, "messages", args_info->messages_orig, 0);
  if (args_info->loss_given)
    write_into_file(outfile, "loss", args_info->loss_orig, 0);
  if (args_info->corruption_given)
    write_into_file(outfile, "corruption", args_info->corruption_orig, 0);
  if (args_info->delay_given)
    write_into_file(outfile, "delay", args_info->delay_orig, 0);
  if (args_info->maxTime_given)
    write_into_file(outfile, "maxTime", args_info->maxTime_orig, 0);
  if (args_info->seed_given)
    write_into_file(outfile, "seed", args_info->seed_orig, 0);
  if (args_info->bidirectional_given)
    write_into_file(outfile, "bidirectional", 0, 0 );
  if (args_info->loglevel_given)
    write_into_file(outfile, "loglevel", args_info->loglevel_orig, 0);
  if (args_info->logfile_given)
    write_into_file(outfile, "logfile", args_info->logfile_orig, 0);
  if (args_info->quiet_given)
    write_into_file(outfile, "quiet", 0, 0 );
  if (args_info->color_given)
    write_into_file(outfile, "color", 0, 0 );
  if (args_info->check_given)
    write_into_file(outfile, "check", 0, 0 );
  if (args_info->stop_on_failure_given)
    write_into_file(outfile, "stop-on-failure", 0, 0 );
  if (args_info->visualize_given)
    write_into_file(outfile, "visualize", args_info->visualize_orig, 0);
  if (args_info->conf_file_given)
    write_into_file(outfile, "conf-file", args_info->conf_file_orig, 0);
  

  i = EXIT_SUCCESS;
  return i;
}

int
cmdline_parser_file_save(const char *filename, struct gengetopt_args_info *args_info)
{
  FILE *outfile;
  int i = 0;

  outfile = fopen(filename, "w");

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot open file for writing: %s\n", CMDLINE_PARSER_PACKAGE, filename);
      return EXIT_FAILURE;
    }

  i = cmdline_parser_dump(outfile, args_info);
  fclose (outfile);

  return i;
}

void
cmdline_parser_free (struct gengetopt_args_info *args_info)
{
  cmdline_parser_release (args_info);
}

/** @brief replacement of strdup, which is not standard */
char *
gengetopt_strdup (const char *s)
{
  char *result = 0;
  if (!s)
    return result;

  result = (char*)malloc(strlen(s) + 1);
  if (result == (char*)0)
    return (char*)0;
  strcpy(result, s);
  return result;
}

int
cmdline_parser (int argc, char **argv, struct gengetopt_args_info *args_info)
{
  return cmdline_parser2 (argc, argv, args_info, 0, 1, 1);
}

int
cmdline_parser_ext (int argc, char **argv, struct gengetopt_args_info *args_info,
                   struct cmdline_parser_params *params)
{
  int result;
  result = cmdline_parser_internal (argc, argv, args_info, params, 0);

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
cmdline_parser2 (int argc, char **argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required)
{
  int result;
  struct cmdline_parser_params params;
  
  params.override = override;
  params.initialize = initialize;
  params.check_required = check_required;
  params.check_ambiguity = 0;
  params.print_errors = 1;

  result = cmdline_parser_internal (argc, argv, args_info, &params, 0);

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
cmdline_parser_required (struct gengetopt_args_info *args_info, const char *prog_name)
{
  FIX_UNUSED (args_info);
  FIX_UNUSED (prog_name);
  return EXIT_SUCCESS;
}


static char *package_name = 0;

/**
 * @brief updates an option
 * @param field the generic pointer to the field to update
 * @param orig_field the pointer to the orig field
 * @param field_given the pointer to the number of occurrence of this option
 * @param prev_given the pointer to the number of occurrence already seen
 * @param value the argument for this option (if null no arg was specified)
 * @param possible_values the possible values for this option (if specified)
 * @param default_value the default value (in case the option only accepts fixed values)
 * @param arg_type the type of this option
 * @param check_ambiguity @see cmdline_parser_params.check_ambiguity
 * @param override @see cmdline_parser_params.override
 * @param no_free whether to free a possible previous value
 * @param multiple_option whether this is a multiple option
 * @param long_opt the corresponding long option
 * @param short_opt the corresponding short option (or '-' if none)
 * @param additional_error possible further error specification
 */
static
int update_arg(void *field, char **orig_field,
               unsigned int *field_given, unsigned int *prev_given, 
               char *value, const char *possible_values[],
               const char *default_value,
               cmdline_parser_arg_type arg_type,
               int check_ambiguity, int override,
               int no_free, int multiple_option,
               const char *long_opt, char short_opt,
               const char *additional_error)
{
  char *stop_char = 0;
  const char *val = value;
  int found;
  char **string_field;
  FIX_UNUSED (field);

  stop_char = 0;
  found = 0;

  if (!multiple_option && prev_given && (*prev_given || (check_ambiguity && *field_given)))
    {
      if (short_opt != '-')
        fprintf (stderr, "%s: `--%s' (`-%c') option given more than once%s\n", 
               package_name, long_opt, short_opt,
               (additional_error ? additional_error : ""));
      else
        fprintf (stderr, "%s: `--%s' option given more than once%s\n", 
               package_name, long_opt,
               (additional_error ? additional_error : ""));
      return 1; /* failure */
    }

  FIX_UNUSED (default_value);
    
  if (field_given && *field_given && ! override)
    return 0;
  if (prev_given)
    (*prev_given)++;
  if (field_given)
    (*field_given)++;
  if (possible_values)
    val = possible_values[found];

  switch(arg_type) {
  case ARG_FLAG:
    *((int *)field) = !*((int *)field);
    break;
  case ARG_INT:
    if (val) *((int *)field) = strtol (val, &stop_char, 0);
    break;
  case ARG_FLOAT:
    if (val) *((float *)field) = (float)strtod (val, &stop_char);
    break;
  case ARG_STRING:
    if (val) {
      string_field = (char **)field;
      if (!no_free && *string_field)
        free (*string_field); /* free previous string */
      *string_field = gengetopt_strdup (val);
    }
    break;
  default:
    break;
  };

  /* check numeric conversion */
  switch(arg_type) {
  case ARG_INT:
  case ARG_FLOAT:
    if (val && !(stop_char && *stop_char == '\0')) {
      fprintf(stderr, "%s: invalid numeric value: %s\n", package_name, val);
      return 1; /* failure */
    }
    break;
  default:
    ;
  };

  /* store the original value */
  switch(arg_type) {
  case ARG_NO:
  case ARG_FLAG:
    break;
  default:
    if (value && orig_field) {
      if (no_free) {
        *orig_field = value;
      } else {
        if (*orig_field)
          free (*orig_field); /* free previous string */
        *orig_field = gengetopt_strdup (value);
      }
    }
  };

  return 0; /* OK */
}


int
cmdline_parser_internal (
  int argc, char **argv, struct gengetopt_args_info *args_info,
                        struct cmdline_parser_params *params, const char *additional_error)
{
  int c;	/* Character of the parsed option.  */

  int error_occurred = 0;
  struct gengetopt_args_info local_args_info;
  
  int override;
  int initialize;
  int check_required;
  int check_ambiguity;
  
  package_name = argv[0];
  
  /* TODO: Why is this here? It is not used anywhere. */
  override = params->override;
  FIX_UNUSED(override);

  initialize = params->initialize;
  check_required = params->check_required;

  /* TODO: Why is this here? It is not used anywhere. */
  check_ambiguity = params->check_ambiguity;
  FIX_UNUSED(check_ambiguity);

  if (initialize)
    cmdline_parser_init (args_info);

  cmdline_parser_init (&local_args_info);

  optarg = 0;
  optind = 0;
  opterr = params->print_errors;
  optopt = '?';

  while (1)
    {
      int option_index = 0;

      static struct option long_options[] = {
        { "help",	0, NULL, 'h' },
        { "version",	0, NULL, 'V' },
        { "messages",	1, NULL, 'm' },
        { "loss",	1, NULL, 'l' },
        { "corruption",	1, NULL, 'c' },
        { "delay",	1, NULL, 'd' },
        { "maxTime",	1, NULL, 't' },
        { "seed",	1, NULL, 's' },
        { "bidirectional",	0, NULL, 'b' },
        { "loglevel",	1, NULL, 'L' },
        { "logfile",	1, NULL, 0 },
        { "quiet",	0, NULL, 'q' },
        { "color",	0, NULL, 'k' },
        { "check",	0, NULL, 0 },
        { "stop-on-failure",	0, NULL, 'f' },
        { "visualize",	1, NULL, 'v' },
        { "conf-file",	1, NULL, 'C' },
        { 0,  0, 0, 0 }
      };

      c = getopt_long (argc, argv, "hVm:l:c:d:t:s:bL:qkfv:C:", long_options, &option_index);

      if (c == -1) break;	/* Exit from `while (1)' loop.  */

      switch (c)
        {
        case 'h':	/* Print help and exit.  */
          cmdline_parser_print_help ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'V':	/* Print version and exit.  */
          cmdline_parser_print_version ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'm':	/* Number of messages to send.  */
        
        
          if (update_arg( (void *)&(args_info->messages_arg), 
               &(args_info->messages_orig), &(args_info->messages_given),
              &(local_args_info.messages_given), optarg, 0, "10", ARG_INT,
              check_ambiguity, override, 0, 0,
              "messages", 'm',
              additional_error))
            goto failure;
        
          break;
        case 'l':	/* Packet loss probability.  */
        
        
          if (update_arg( (void *)&(args_info->loss_arg), 
               &(args_info->loss_orig), &(args_info->loss_given),
              &(local_args_info.loss_given), optarg, 0, "0.0", ARG_FLOAT,
              check_ambiguity, override, 0, 0,
              "loss", 'l',
              additional_error))
            goto failure;
        
          break;
        case 'c':	/* Packet corruption probability.  */
        
        
          if (update_arg( (void *)&(args_info->corruption_arg), 
               &(args_info->corruption_orig), &(args_info->corruption_given),
              &(local_args_info.corruption_given), optarg, 0, "0.0", ARG_FLOAT,
              check_ambiguity, override, 0, 0,
              "corruption", 'c',
              additional_error))
            goto failure;
        
          break;
        case 'd':	/* Average delay between packets.  */
        
        
          if (update_arg( (void *)&(args_info->delay_arg), 
               &(args_info->delay_orig), &(args_info->delay_given),
              &(local_args_info.delay_given), optarg, 0, "5.0", ARG_FLOAT,
              check_ambiguity, override, 0, 0,
              "delay", 'd',
              additional_error))
            goto failure;
        
          break;
        case 't':	/* Maximum time to run the simulation.  */
        
        
          if (update_arg( (void *)&(args_info->maxTime_arg), 
               &(args_info->maxTime_orig), &(args_info->maxTime_given),
              &(local_args_info.maxTime_given), optarg, 0, "200.0", ARG_FLOAT,
              check_ambiguity, override, 0, 0,
              "maxTime", 't',
              additional_error))
            goto failure;
        
          break;
        case 's':	/* Seed for the random number generator.  */
        
        
          if (update_arg( (void *)&(args_info->seed_arg), 
               &(args_info->seed_orig), &(args_info->seed_given),
              &(local_args_info.seed_given), optarg, 0, "42", ARG_INT,
              check_ambiguity, override, 0, 0,
              "seed", 's',
              additional_error))
            goto failure;
        
          break;
        case 'b':	/* If set, the channel will be bidirectional.  */
        
        
          if (update_arg((void *)&(args_info->bidirectional_flag), 0, &(args_info->bidirectional_given),
              &(local_args_info.bidirectional_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "bidirectional", 'b',
              additional_error))
            goto failure;
        
          break;
        case 'L':	/* Logging level.  */
        
        
          if (update_arg( (void *)&(args_info->loglevel_arg), 
               &(args_info->loglevel_orig), &(args_info->loglevel_given),
              &(local_args_info.loglevel_given), optarg, 0, "2", ARG_INT,
              check_ambiguity, override, 0, 0,
              "loglevel", 'L',
              additional_error))
            goto failure;
        
          break;
        case 'q':	/* If set, the program won't print anything to stdout.  */
        
        
          if (update_arg((void *)&(args_info->quiet_flag), 0, &(args_info->quiet_given),
              &(local_args_info.quiet_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "quiet", 'q',
              additional_error))
            goto failure;
        
          break;
        case 'k':	/* If set, the program will use colors in the output.  */
        
        
          if (update_arg((void *)&(args_info->color_flag), 0, &(args_info->color_given),
              &(local_args_info.color_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "color", 'k',
              additional_error))
            goto failure;
        
          break;
        case 'f':	/* If set, the simulator will continue even if the messages are not received in the correct order.  */
        
        
          if (update_arg((void *)&(args_info->stop_on_failure_flag), 0, &(args_info->stop_on_failure_given),
              &(local_args_info.stop_on_failure_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "stop-on-failure", 'f',
              additional_error))
            goto failure;
        
          break;
        case 'v':	/* If set, the simulator will export an svg file with the visualization of the simulation.  */
        
        
          if (update_arg( (void *)&(args_info->visualize_arg), 
               &(args_info->visualize_orig), &(args_info->visualize_given),
              &(local_args_info.visualize_given), optarg, 0, 0, ARG_STRING,
              check_ambiguity, override, 0, 0,
              "visualize", 'v',
              additional_error))
            goto failure;
        
          break;
        case 'C':	/* If set, the simulator will read the configuration from this file.  */
        
        
          if (update_arg( (void *)&(args_info->conf_file_arg), 
               &(args_info->conf_file_orig), &(args_info->conf_file_given),
              &(local_args_info.conf_file_given), optarg, 0, 0, ARG_STRING,
              check_ambiguity, override, 0, 0,
              "conf-file", 'C',
              additional_error))
            goto failure;
        
          break;

        case 0:	/* Long option with no short option */
          /* If set, the logging will also be written to this file.  */
          if (strcmp (long_options[option_index].name, "logfile") == 0)
          {
          
          
            if (update_arg( (void *)&(args_info->logfile_arg), 
                 &(args_info->logfile_orig), &(args_info->logfile_given),
                &(local_args_info.logfile_given), optarg, 0, 0, ARG_STRING,
                check_ambiguity, override, 0, 0,
                "logfile", '-',
                additional_error))
              goto failure;
          
          }
          /* If set, the simulator will check that the payloads are received in the correct order.  */
          else if (strcmp (long_options[option_index].name, "check") == 0)
          {
          
          
            if (update_arg((void *)&(args_info->check_flag), 0, &(args_info->check_given),
                &(local_args_info.check_given), optarg, 0, 0, ARG_FLAG,
                check_ambiguity, override, 1, 0, "check", '-',
                additional_error))
              goto failure;
          
          }
          
          break;
        case '?':	/* Invalid option.  */
          /* `getopt_long' already printed an error message.  */
          goto failure;

        default:	/* bug: option not considered.  */
          fprintf (stderr, "%s: option unknown: %c%s\n", CMDLINE_PARSER_PACKAGE, c, (additional_error ? additional_error : ""));
          abort ();
        } /* switch */
    } /* while */



	FIX_UNUSED(check_required);

  cmdline_parser_release (&local_args_info);

  if ( error_occurred )
    return (EXIT_FAILURE);

  return 0;

failure:
  
  cmdline_parser_release (&local_args_info);
  return (EXIT_FAILURE);
}

#ifndef CONFIG_FILE_LINE_SIZE
#define CONFIG_FILE_LINE_SIZE 2048
#endif
#define ADDITIONAL_ERROR " in configuration file "

#define CONFIG_FILE_LINE_BUFFER_SIZE (CONFIG_FILE_LINE_SIZE+3)
/* 3 is for "--" and "=" */

static int
_cmdline_parser_configfile (const char *filename, int *my_argc)
{
  FILE* file;
  char my_argv[CONFIG_FILE_LINE_BUFFER_SIZE+1];
  char linebuf[CONFIG_FILE_LINE_SIZE];
  int line_num = 0;
  int result = 0, equal;
  char *fopt, *farg;
  char *str_index;
  size_t len, next_token;
  char delimiter;

  if ((file = fopen(filename, "r")) == 0)
    {
      fprintf (stderr, "%s: Error opening configuration file '%s'\n",
               CMDLINE_PARSER_PACKAGE, filename);
      return EXIT_FAILURE;
    }

  while ((fgets(linebuf, CONFIG_FILE_LINE_SIZE, file)) != 0)
    {
      ++line_num;
      my_argv[0] = '\0';
      len = strlen(linebuf);
      if (len > (CONFIG_FILE_LINE_BUFFER_SIZE-1))
        {
          fprintf (stderr, "%s:%s:%d: Line too long in configuration file\n",
                   CMDLINE_PARSER_PACKAGE, filename, line_num);
          result = EXIT_FAILURE;
          break;
        }

      /* find first non-whitespace character in the line */
      next_token = strspn (linebuf, " \t\r\n");
      str_index  = linebuf + next_token;

      if ( str_index[0] == '\0' || str_index[0] == '#')
        continue; /* empty line or comment line is skipped */

      fopt = str_index;

      /* truncate fopt at the end of the first non-valid character */
      next_token = strcspn (fopt, " \t\r\n=");

      if (fopt[next_token] == '\0') /* the line is over */
        {
          farg  = 0;
          equal = 0;
          goto noarg;
        }

      /* remember if equal sign is present */
      equal = (fopt[next_token] == '=');
      fopt[next_token++] = '\0';

      /* advance pointers to the next token after the end of fopt */
      next_token += strspn (fopt + next_token, " \t\r\n");

      /* check for the presence of equal sign, and if so, skip it */
      if ( !equal )
        if ((equal = (fopt[next_token] == '=')))
          {
            next_token++;
            next_token += strspn (fopt + next_token, " \t\r\n");
          }
      str_index  += next_token;

      /* find argument */
      farg = str_index;
      if ( farg[0] == '\"' || farg[0] == '\'' )
        { /* quoted argument */
          str_index = strchr (++farg, str_index[0] ); /* skip opening quote */
          if (! str_index)
            {
              fprintf
                (stderr,
                 "%s:%s:%d: unterminated string in configuration file\n",
                 CMDLINE_PARSER_PACKAGE, filename, line_num);
              result = EXIT_FAILURE;
              break;
            }
        }
      else
        { /* read up the remaining part up to a delimiter */
          next_token = strcspn (farg, " \t\r\n#\'\"");
          str_index += next_token;
        }

      /* truncate farg at the delimiter and store it for further check */
      delimiter = *str_index, *str_index++ = '\0';

      /* everything but comment is illegal at the end of line */
      if (delimiter != '\0' && delimiter != '#')
        {
          str_index += strspn(str_index, " \t\r\n");
          if (*str_index != '\0' && *str_index != '#')
            {
              fprintf
                (stderr,
                 "%s:%s:%d: malformed string in configuration file\n",
                 CMDLINE_PARSER_PACKAGE, filename, line_num);
              result = EXIT_FAILURE;
              break;
            }
        }

    noarg:
      if (!strcmp(fopt,"include")) {
        if (farg && *farg) {
          result = _cmdline_parser_configfile(farg, my_argc);
        } else {
          fprintf(stderr, "%s:%s:%d: include requires a filename argument.\n",
                  CMDLINE_PARSER_PACKAGE, filename, line_num);
        }
        continue;
      }
      len = strlen(fopt);
      strcat (my_argv, len > 1 ? "--" : "-");
      strcat (my_argv, fopt);
      if (len > 1 && ((farg && *farg) || equal))
        strcat (my_argv, "=");
      if (farg && *farg)
        strcat (my_argv, farg);
      ++(*my_argc);

      cmd_line_list_tmp = (struct line_list *) malloc (sizeof (struct line_list));
      cmd_line_list_tmp->next = cmd_line_list;
      cmd_line_list = cmd_line_list_tmp;
      cmd_line_list->string_arg = gengetopt_strdup(my_argv);
    } /* while */

  if (file)
    fclose(file);
  return result;
}

int
cmdline_parser_configfile (
  const char *filename,
                           struct gengetopt_args_info *args_info,
                           int override, int initialize, int check_required)
{
  struct cmdline_parser_params params;

  params.override = override;
  params.initialize = initialize;
  params.check_required = check_required;
  params.check_ambiguity = 0;
  params.print_errors = 1;
  
  return cmdline_parser_config_file (filename, args_info, &params);
}

int
cmdline_parser_config_file (const char *filename,
                           struct gengetopt_args_info *args_info,
                           struct cmdline_parser_params *params)
{
  int i, result;
  int my_argc = 1;
  char **my_argv_arg;
  char *additional_error;

  /* store the program name */
  cmd_line_list_tmp = (struct line_list *) malloc (sizeof (struct line_list));
  cmd_line_list_tmp->next = cmd_line_list;
  cmd_line_list = cmd_line_list_tmp;
  cmd_line_list->string_arg = gengetopt_strdup (CMDLINE_PARSER_PACKAGE);

  result = _cmdline_parser_configfile(filename, &my_argc);

  if (result != EXIT_FAILURE) {
    my_argv_arg = (char **) malloc((my_argc+1) * sizeof(char *));
    cmd_line_list_tmp = cmd_line_list;

    for (i = my_argc - 1; i >= 0; --i) {
      my_argv_arg[i] = cmd_line_list_tmp->string_arg;
      cmd_line_list_tmp = cmd_line_list_tmp->next;
    }

    my_argv_arg[my_argc] = 0;

    additional_error = (char *)malloc(strlen(filename) + strlen(ADDITIONAL_ERROR) + 1);
    strcpy (additional_error, ADDITIONAL_ERROR);
    strcat (additional_error, filename);
    result =
      cmdline_parser_internal (my_argc, my_argv_arg, args_info,
                              params,
                              additional_error);

    free (additional_error);
    free (my_argv_arg);
  }

  free_cmd_list();
  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}
/* vim: set ft=c noet ts=8 sts=8 sw=8 tw=80 nojs spell : */
