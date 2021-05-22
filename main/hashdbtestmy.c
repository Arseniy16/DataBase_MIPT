#line 827 "hashdb.nw"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "hashdb.h"
#define BLOCK 1000
#define BLOCK2 BLOCK*2
#define STEP 100

struct timespec mt1, mt2;
double ftime, simple_time;
double time_array[BLOCK2];

int main(int argc, char* argv[]) {
	DB* dbh;
	char buf[4096];
	if (argc < 2) {
		printf("usage: %s <dbfilename>\n", argv[0]);
		exit(1);
	}
	dbh = ht_open(argv[1], 141307);
	if ( !dbh ) {
		printf("Cannot open database %s\n", argv[1]);
		exit(1);
	}
	FILE* input = fopen("instructions.txt","r");
	int i = 0;
	while(fgets(buf, 4096, input)){
		char* s = buf;
		char* cmd = strsep(&s, " \t\n");
		if ( cmd ) {
			if (!strcmp(cmd, "SET")) {
				char* key = strsep(&s, " \t\n");
				char* val = strsep(&s, "\n");
				clock_gettime(CLOCK_REALTIME, &mt1);
				if (key && val) {
					ht_set(dbh, key, val);
				} else 
				  printf("No key or val given\n");
				clock_gettime(CLOCK_REALTIME, &mt2);
				ftime = 1000000000*(mt2.tv_sec-mt1.tv_sec)+(mt2.tv_nsec-mt1.tv_nsec);
				simple_time = (double) ftime/1000000;
				time_array[i] = simple_time;
				i++;
			} else if ( !strcmp(cmd, "GET")) {
				clock_gettime(CLOCK_REALTIME, &mt1);
				char* key = strsep(&s, " \t\n");
				if ( key ) {
					char* val;
					if ( ht_get(dbh, key, &val) ) {
//						printf("%s\n", val);
						free(val);
					} else {
						printf("No such key\n");
					}
				}
				clock_gettime(CLOCK_REALTIME, &mt2);
				ftime = 1000000000*(mt2.tv_sec-mt1.tv_sec)+(mt2.tv_nsec-mt1.tv_nsec);
				simple_time = (double) ftime/1000000;
				time_array[i] = simple_time;
				i++;
			} else if ( !strcmp(cmd, "DEL")) {
				char* key = strsep(&s, " \t\n");
				if ( key ) {
					ht_del(dbh, key);
					printf("OK\n");
				}
			} else if ( !strcmp(cmd, "STAT")) {
				Stat stat;
				ht_get_stat(dbh, &stat);
				printf("Keys: %lu\n tables: %u\nAvg. key size: %f\n"
					"Avg. value size: %f\n"
					"Total capacity: %lu\n"
					"Avg. Fill factor: %f\n"
					"Max chain length: %u\n"
					"Filled nodes: %lu\n"
					"Node fill factor: %f\n"
					"Avg chain length: %f\n",
					stat.keys, stat.tables,
					stat.keysz/(float)stat.keys,
					stat.valuesz/(float)stat.keys,
					stat.capacity,
					stat.keys/(float)stat.capacity,
					stat.maxlen,
					stat.nodes,
					stat.nodes/(float)stat.capacity,
					stat.keys/(float)stat.nodes);
			} else if ( !strcmp(cmd, "MASS")) { 
				char *start = strsep(&s, " \t\n");
				char *count = strsep(&s, " \t\n");
				if (start && count) {
					int i;
					int st = atoi(start);
					int cnt = atoi(count);
//					printf("Starting set from %d to %d\n", st, st+cnt);
					for ( i = st; i<= st+cnt; i++) {
						char key[100];
						char value[100];
						snprintf(key, 100, "key%d", i);
						snprintf(value, 100, "value%d", i);
						ht_set(dbh, key, value);
					}
				}
			}
			else if ( !strcmp(cmd, "QUIT") || !strcmp(cmd, "EXIT")) {
				break;
			} else {
				printf("unknown command\n");
			}
		}
	}
	fclose(input);
	FILE* output = fopen(argv[2], "w");
	fprintf(output, "------------------------------------------------\n");
	fprintf(output, "NUMBER OF KEYS\n");
	for(int j = 199; j < BLOCK; j = j + STEP) {
		fprintf(output, "%d\n", j);
	}
	fprintf(output, "------------------------------------------------\n");
	fprintf(output, "TIME\n");
	for(int j = 0; j < i; j++) {
		fprintf(output, "%lg\n", time_array[j]);
	}
	fprintf(output, "------------------------------------------------\n");
	fclose(output);
	ht_close(dbh);
	return 0;
}