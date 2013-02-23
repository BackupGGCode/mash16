/*
 *   mash16 - the chip16 emulator
 *   Copyright (C) 2012-2013 tykel
 *
 *   mash16 is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   mash16 is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with mash16.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "options.h"
#include "strings.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void options_parse(int argc, char** argv, program_opts* opts)
{
    if(argc < 2)
    {
        fprintf(stderr,"warning: no filename supplied, exiting...\n");
        exit(0);
    }
    else if(!strncmp(argv[1],"--help",MAX_STRING))
    {
        printf(str_help);
        exit(0);
    }
    else if(!strncmp(argv[1],"--version",MAX_STRING))
    {
        printf("mash16 %d.%d.%d (#%s) -- the chip16 emulator\n",MAJOR,MINOR,REV,BUILD);
        exit(0);
    }
    else if(argv[1][0] == '-')
    {
        fprintf(stderr,"warning: no filename supplied, exiting...\n");
        exit(0);
    }
    opts->filename = argv[1];
    if(argc > 2)
    {
        for(int i=2; i<argc; ++i)
        {
            if(!strncmp(argv[i],"--no-audio", MAX_STRING))
            {
                opts->use_audio = 0;
            }
            else if(!strncmp(argv[i],"--audio-sample-rate",19))
            {
                char *num;
                if(strlen(argv[i]) > 20 && argv[i][19] == '=')
                    num = &argv[i][20];
                else if(i+1 < argc)
                    num = argv[++i];
                else
                {
                    fprintf(stderr,"error: no audio sample rate provided\n");
                    continue;
                }

                long int rate = strtol(num,NULL,0);
                if(!rate)
                    fprintf(stderr,"error: invalid input '%s'\n",num);
                else
                    opts->audio_sample_rate = rate;
            }
            else if(!strncmp(argv[i],"--audio-buffer",14))
            {
                char *num;
                if(strlen(argv[i]) > 15 && argv[i][14] == '=')
                    num = &argv[i][15];
                else if(i+1 < argc)
                    num = argv[++i];
                else
                {
                    fprintf(stderr,"error: no audio buffer size provided\n");
                    continue;
                }

                long int size = strtol(num,NULL,0);
                if(!size)
                    fprintf(stderr,"error: invalid input '%s'\n",num);
                else
                    opts->audio_buffer_size = size;

            }
            else if(!strncmp(argv[i],"--audio-volume",14))
            {
                char *num;
                if(strlen(argv[i]) > 15 && argv[i][14] == '=')
                    num = &argv[i][15];
                else if(i+1 < argc)
                    num = argv[++i];
                else
                {
                    fprintf(stderr,"error: no volume amount provided\n");
                    continue;
                }

                long int vol = strtol(num,NULL,0);
                if(!vol)
                    fprintf(stderr,"error: invalid input '%s'\n",num);
                else
                    opts->audio_volume = vol;

            }
            else if(!strncmp(argv[i],"--verbose",MAX_STRING))
            {
                opts->use_verbose = 1;
            }
            else if(!strncmp(argv[i],"--break",7))
            {
                if(!strncmp(argv[i],"--break-all",MAX_STRING))
                {
                    opts->use_breakall = 1;
                    continue;
                }
                char *n, *nums;
                if(strlen(argv[i]) > 8 && argv[i][7] == '@')
                {
                    nums = &argv[i][8];
                    n = strtok(nums,", ");
                    while(n != NULL)
                    {
                        int i = opts->num_breakpoints++;
                        opts->breakpoints[i] = strtol(n,NULL,0);
                        n = strtok(NULL,", ");
                    }
                }
                else
                {
                    fprintf(stderr,"error: no breakpoint specified\n");
                    exit(1);
                }
            }
            else if(!strncmp(argv[i],"--fullscreen",MAX_STRING))
            {
                opts->use_fullscreen = 1;
            }
            else if(!strncmp(argv[i],"--video-scaler",14))
            {
                char *num;
                if(strlen(argv[i]) > 15 && argv[i][14] == '=')
                    num = &argv[i][15];
                else if(i+1 < argc)
                    num = argv[++i];
                else
                {
                    fprintf(stderr,"error: no video scale provided\n");
                    continue;
                }
                
                long int scale = strtol(num,NULL,0);
                if(!scale)
                    fprintf(stderr,"error: invalid input '%s'\n",num);
                else
                    opts->video_scaler = scale;
            }
            else if(!strncmp(argv[i],"--no-cpu-limit",MAX_STRING))
            {
                opts->use_cpu_limit = 0;
            }
            else if(!strncmp(argv[i],"--cpu-rec",MAX_STRING))
            {
                opts->use_cpu_rec = 1;
            }
            else if(!strncmp(argv[i],"--help",MAX_STRING))
            {
                printf(str_help);
            }
            else if(!strncmp(argv[i],"--version",MAX_STRING))
            {
                printf("mash16 %d.%d.%d (#%s) -- the chip16 emulator\n",MAJOR,MINOR,REV,BUILD);
            }
            else
            {
                fprintf(stderr,"warning: invalid option '%s', ignoring\n",argv[i]);
            }
        }    
    }
}

