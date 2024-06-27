#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include "libft.h"

#define RESET "\033[0m"

#define BLACK      "\033[0;30m"
#define RED        "\033[0;31m"
#define GREEN      "\033[0;32m"
#define YELLOW     "\033[0;33m"
#define BLUE       "\033[0;34m"
#define MAGENTA    "\033[0;35m"
#define CYAN       "\033[0;36m"
#define WHITE      "\033[0;37m"

#define BOLD_BLACK     "\033[1;30m"
#define BOLD_RED       "\033[1;31m"
#define BOLD_GREEN     "\033[1;32m"
#define BOLD_YELLOW    "\033[1;33m"
#define BOLD_BLUE      "\033[1;34m"
#define BOLD_MAGENTA   "\033[1;35m"
#define BOLD_CYAN      "\033[1;36m"
#define BOLD_WHITE     "\033[1;37m"

#define UNDERLINE_BLACK     "\033[4;30m"
#define UNDERLINE_RED       "\033[4;31m"
#define UNDERLINE_GREEN     "\033[4;32m"
#define UNDERLINE_YELLOW    "\033[4;33m"
#define UNDERLINE_BLUE      "\033[4;34m"
#define UNDERLINE_MAGENTA   "\033[4;35m"
#define UNDERLINE_CYAN      "\033[4;36m"
#define UNDERLINE_WHITE     "\033[4;37m"

#define BACKGROUND_BLACK   "\033[40m"
#define BACKGROUND_RED     "\033[41m"
#define BACKGROUND_GREEN   "\033[42m"
#define BACKGROUND_YELLOW  "\033[43m"
#define BACKGROUND_BLUE    "\033[44m"
#define BACKGROUND_MAGENTA "\033[45m"
#define BACKGROUND_CYAN    "\033[46m"
#define BACKGROUND_WHITE   "\033[47m"

#define MAX_LINE_LENGTH 2002 /* fgets() need space for NUL after newline */
#define MAX_PRINT_LEN 100
#define TESTBUFFSZ 3000

#define CC "cc"
#define CFLAGS "-Wall -Wextra -Werror -o"
#define LIB "libft.a"
#define EXNAMELG "testproglg"
#define EXNAMESM "testprogsm"
#define EXNAME1 "testprogone"
#define THISPROG "gnl_test_suite.c"
#define TESTPROG "get_next_line_utils.c get_next_line.c"
#define TESTFUNC get_next_line

#define FILE2K "2k.txt"
#define FILE1 "Basic.txt"
#define CHAR3FILE "3char.txt"
#define CHAR2FILE "2char.txt"
#define CHAR4FILE "4char.txt"
#define EMPTYFILE "empty.txt"
#define CHARFILE "1char.txt"
#define DUMMYFILE "dummy"
#define MULTIFILE "multi"

#define VAR2INJ "BUFFER_SIZE"
#define BUFFLG 3000
#define BUFFSM 3
#define STDIN 0

#define EXPFILE2K "Madman drummers bummers and Indians in the summer With a teenage diplomat In the dumps with the mumps As the adolescent pumps his way into his hat With a boulder on my shoulder, feelin' kinda older I tripped the merry-go-round With this very unpleasing sneezing and wheezing The calliope crashed to the ground Some all-hot half-shot was headin' for the hot spot Snappin' his fingers, clappin' his hands And some fleshpot mascot was tied into a lover's knot With a whatnot in her hand And now young Scott with a slingshot Finally found a tender spot and throws his lover in the sand And some bloodshot forget-me-not whispers Daddy's within earshot, save the buckshot, turn up the band And she was blinded by the light Oh, cut loose like a deuce, another runner in the night Blinded by the light She got down but she never got tight But she'll make it alright Some brimstone baritone anti-cyclone Rolling stone preacher from the East He says, dethrone the dictaphone Hit it in its funny bone, that's where they expect it least And some new-mown chaperone was standin' in the corner all alone Watchin' the young girls dance And some fresh-sown moonstone was messin' with his frozen zone To remind him of the feeling of romance Yeah, he was blinded by the light Oh, cut loose like a deuce, another runner in the night Blinded by the light He got down but he never got tight, but he's gonna make it tonight Some silicone sister with her manager's mister Told me I got what it takes She said, I'll turn you on, sonny To something strong if you'll play that song with the funky break And Go-Cart Mozart was checkin' out the weather chart To see if it was safe to go outside And little Early-Pearly came by in her curly-wurly And asked me if I needed a ride Oh, some hazard from Harvard was skunked on beer Playin' backyard bombardier Yes, and Scotland Yard was trying hard They sent some dude with a calling card He said, do what you like, but don't do it here Well, I jumped up, turned around, spit in the \n" \
				"I'm packed and I'm holding, I'm smiling, she's living, she's golden and she lives for me, says she lives for me, Ovation, what a motivation, she comes round and she goes down on me, And I make her smile, like a drug for you, Do ever what you want to do, Coming over you, Keep on smiling, what we go through. One stop to the rhythm that divides you, And I speak to you like the to the verse, Chop another line like a coda with a curse, come on like a freak show takes the stage. We give them the games we play, she say, I want something else, to get me through this, Semi-charmed kind of life baby, baby, I want something else, I'm not listening when you say, Good-bye. The sky it was gold, it was rose, I was taking sips of it through my nose, And I wish I could get back there, Some place back there, Smiling in the pictures you would take, Doing crystal myth, Will lift you up until you break, It won't stop, I won't come down, I keep stock, With a tick tock rhythm a bump for the drop, And then I bumped up. I took the hit I was given, And I bumped again, And I bumped again. How do I get back there to, The place where I fell asleep inside you? How do I get myself back to, The place where you said, I want something else to get me through this, semi-charmed kind of life baby, baby, I want something else, I'm not listening when you say, good-bye, I believe in the sand beneath my toes, The beach gives a feeling, An earthy feeling, I believe in the faith that grows, And the four right chords can make me cry, When I'm with you I feel like I could die. And that would be all right, All right, When the plane came in, She said she was crashing, The velvet it rips, In the city we tripped, On the urge to feel alive, But now I'm struggling to survive, Those days you were wearing, That velvet dress, You're the priestess, I must confess, Those little red panties, They pass the test, Slide up around the belly, Face down on the mattress, One, And you hold me, And we're broken. Still it's all tha\n" \
				"Ah, breaker one-nine, this here's the Rubber Duck You got a copy on me, Pig Pen, c'mon? Ah, yeah, 10-4, Pig Pen, fer shure, fer shure By golly, it's clean clear to Flag Town, c'mon Yeah, that's a big 10-4 there, Pig Pen Yeah, we definitely got the front door, good buddy Mercy sakes alive, looks like we got us a convoy Was the dark of the moon on the sixth of June In a Kenworth pullin' logs Cab-over Pete with a reefer on And a Jimmy haulin' hogs We was headin' for Bexar on I one-oh 'Bout a mile outta Shaky Town I says, Pig Pen, this here's the Rubber Duck And I'm about to put the hammer down 'Cause we got a little ol' convoy Rockin' through the night Yeah, we got a little ol' convoy Ain't she a beautiful sight? Come on and join our convoy Ain't nothin' gonna get in our way We gonna roll this truckin' convoy Across the USA Convoy Ah, breaker, Pig Pen, this here's the duck And, uh, you wanna back off them hogs? (Convoy) Uh, 10-4, 'bout five mile or so, ten, roger Them hogs is gettin' intense up here By the time we got into Tulsa town We had eighty-five trucks in all But there's a roadblock up on the cloverleaf And them bears was wall-to-wall Yeah, them Smokeys as thick as bugs on a bumper They even had a bear in the air I says, callin' all trucks, this here's the duck We about to go a-huntin' bear 'Cause we got a great big convoy Rockin' through the night Yeah, we got a great big convoy Ain't she a beautiful sight? Come on and join our convoy Ain't nothin' gonna get in our way We gonna roll this truckin' convoy Across the USA Convoy Ah, you wanna give me a 10-9 on that, Pig Pen? (Convoy) Negatory, Pig Pen, you're still too close Yeah, them hogs is startin' to close up my sinuses Mercy sakes, you better back off another ten Well, we rolled up Interstate 44 Like a rocket sled on rails We tore up all of our swindle sheets And left 'em settin' on the scales By the time we hit that Chi-town Them bears was a-gettin' smart They'd brought up some reinforcements From the Illino"
#define EXPLN2K 3
#define EXPFILE1 "I don't mind stealin' bread from the mouths of decadents\n" \
				"But I can't feed on the powerless when my cup's already overfilled, yeah\n" \
				"But it's on the table, the fire's cookin'\n" \
				"And they're farmin' babies, while slaves are workin'\n" \
				"The blood is on the table and the mouths are chokin'\n" \
				"But I'm goin' hungry, yeah"
#define EXPLNF1 6
#define EXP4CHAR "abcd\nefgh\nijkl\nmnop\nqr"
#define EXPLN4 5
#define EXP3CHAR "abc\ndef\nghi\njkl\nmno\npqr"
#define EXPLN3 3
#define EXP5CHAR "abcde\nfghij\nklmno\npqr"
#define EXPLN5 4
#define EXP2CHAR "ab\ncd\nef\ngh\nij"
#define EXPLN2 5
#define EXP1CHAR "a\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\nn\no\np\nq\nr"
#define EXPLN1 18
#define EXPEMPTY "\n\n\n"
#define EXPLNEMP 3
#define EXPDUMMY ""

#define MSG1 "Test 1: Large Buffer"
#define MSG2 "Test 2: Small Buffer"
#define MSG3 "Test 3: 1 char Buffer"
#define MSG4 "Test 4: Buffer equal to line len"
#define MSG5 "Test 5: Buffer 1 less than line len"
#define MSG6 "Test 6: Buffer 1 more than line len"
#define MSG7 "Test 7: stdin"
#define MSG8 "Test 8: (inspecific)"
#define MSG9 "Test 9: Long line file"
#define MSG10 "Test 10: Short line file"
#define MSG11 "Test 11: Empty file"
#define MSG12 "Test 12: Multi file read"

#define PRINT_COLOR(color, text) printf(color "%s" RESET "\n", text)
#define ASSERT_WITH_MESSAGE(condition, expected, message) \
	do { \
		if (!(condition)) { \
			fprintf(stderr, RED "%s FAILED.\n" YELLOW "Expected result: \"%.100s [...]$\"" \
						RESET "\n", (message), (expected)); \
			successflag = 1; \
		} else if (expected) { \
			printf(GREEN "%.100s PASSED.\n" YELLOW "Expected result: \"%.100s [...]$\"" \
				   	RESET "\n", (message), (expected)); \
		} else { \
			printf(GREEN "Test Case PASSED" RESET "\n"); \
		} \
	} while (0)
static bool running_lg;
static bool running_sm;
static bool running_ex1;
static bool running_test;

// Function to check if a file exists
static int 
file_exists(const char *filename) {
    return access(filename, F_OK) != -1;
}

// Function to check if a process is running
bool process_is_running(const char *process_name) {
    char command[256];
    sprintf(command, "pgrep -x %s > /dev/null", process_name);
    return system(command) == 0;
}

// Function to create a lock file for the given process name
void create_lock_file(const char *process_name) {
    char lock_file[256];
    sprintf(lock_file, "%s.lock", process_name);
    FILE *file = fopen(lock_file, "w");
    if (file != NULL) {
        fclose(file);
    }
}

// Function to remove the lock file for the given process name
void remove_lock_file(const char *process_name) {
    char lock_file[256];
    sprintf(lock_file, "%s.lock", process_name);
    remove(lock_file);
}

static void
fill_header(char* header, const char *msg, unsigned int line_num)
{
	strcpy(header, "## ");
	strcat(header, msg);
	strcat(header, ": Line "); 
	strcat(header, ft_itoa(line_num));
	return ;
}

static bool
test_stdin_read(char *(*f)(int), const char *msg) {
	printf(BOLD_MAGENTA"Type \"exp\" to pass this test: "RESET);
	fflush(stdout);

	char *buffer;
	char header[100];
	int successflag = 0;

	buffer = f(fileno(stdin));
	if (buffer == NULL) {
		fprintf(stderr, "Error reading from stdin\n");
		return false;
	}
	fill_header(header, msg, 0);
	ASSERT_WITH_MESSAGE(strncmp(buffer, "exp\n", ft_strlen("exp") + 1) == 0, \
			"exp\n" ,header);
	if (successflag == 1)
		return false;
	printf("## " YELLOW "Buffer: %.100s$\n\n" RESET, buffer);
	free(buffer);
	return true;
}

static bool
test_file_multi_read(char *(*f)(int), const char *fn1, const char *fn2, \
		const char *expected1, const char *expected2, const char *msg, unsigned int maxlines1, \
		unsigned int maxlines2) 
{
	FILE *file1 = fopen(fn1, "r"); FILE *file2 = fopen(fn2, "r");
	if (file1 == NULL || file2 == NULL) {
		fprintf(stderr, "Error opening files\n");
		return false;
	}
	bool stop1 = false; bool stop2 = false;
	char *result1; char *result2; char *result;
	char header[100];
	char *p1 = (char*)expected1; char *p2 = (char*)expected2;
	char *refline;
	unsigned int line_num1 = 1; unsigned int line_num2 = 1; unsigned int line_num = 1;
	size_t llen = 0 ;
	int successflag = 0;

	while (1) {
		result1 = f(fileno(file1));
		result2 = f(fileno(file2));
		if (result1 == NULL) {
			result1 = "";
			stop1 = true;
		}
		if (result2 == NULL) {
			result2 = "";
			stop2 = true;
		}
		int i = 0;
		while (i < 2) {
			if (stop1 != true && i % 2 != 0) {
				llen = ft_strchr(p1, '\n') - p1 + 1;
				refline = ft_substr(expected1, p1 - expected1, llen);
				result = result1;
				line_num = line_num1++;
				if (line_num > maxlines1) {
					printf(CYAN"Reached end of file1.\n"RESET); fflush(stdout);
					i++;
					continue ;
				}
				p1 += llen;
			} else if (stop2 != true && i % 2 != 1) {
				llen = ft_strchr(p2, '\n') - p2 + 1;
				refline = ft_substr(expected2, p2 - expected2, llen);
				result = result2;
				line_num = line_num2++;
				if (line_num > maxlines2) {
					printf(CYAN"Reached end of file2.\n"RESET); fflush(stdout);
					i++;
					continue ;
				}
				p2 += llen;
			} else {
				break ;
			}
			fill_header(header, msg, line_num);
			ASSERT_WITH_MESSAGE(strcmp(result, refline) == 0, refline, header);
			printf("## " YELLOW "Result: %.100s$\n\n" RESET, result);
			if (successflag == 1)
			{
				fclose(file1); fclose(file2);
				return false;
			}
			i++;
		}
		free(result1); free(result2);
		if (line_num1 > maxlines1 && line_num2 > maxlines2)
			break ;
	}
	fclose(file1); fclose(file2);
	return true;
}

static bool
test_file_read(char *(*f)(int), const char *fn,  \
		const char *expected, const char *msg, unsigned int maxlines) {
	FILE *file = fopen(fn, "r");
	if (file == NULL) {
		fprintf(stderr, "Error opening file\n");
		return false;
	}
	char *result;
	char header[100];
	char *p = (char*)expected;
	char *refline;
	unsigned int line_num = 1;
	size_t llen = 0;
	int	successflag = 0;
	
	while (line_num <= maxlines) {
		result = f(fileno(file));
		if (result == NULL)
			result = "";
		llen = ft_strchr(p, '\n') - p + 1; /* returns location of chr so add 1 for inclusiveness */
		fill_header(header, msg, line_num);
		refline = ft_substr(expected, p - expected, llen);
		ASSERT_WITH_MESSAGE(strcmp(result, refline) == 0, refline, header);
		printf("## " YELLOW "Result: %.100s$\n\n" RESET, result);
		if (successflag == 1)
		{
			fclose(file);
			return false;
		}
		p += llen;
		line_num++;
		free(result);
	}
	fclose(file);
	return true;
}

int
test(char *(*f)(int), const char *fn,  \
		const char *exp, const char *msg, const unsigned int maxlines) {
	printf("### Test: %s\n", msg); fflush(stdout);
	if (strcmp(fn, DUMMYFILE) == 0) 
	{
		if (!test_stdin_read(f, msg))
			return 1;
	} 
	else if (strcmp(fn, MULTIFILE) == 0)
	{
		if (!test_file_multi_read(f, FILE1, CHAR3FILE, EXPFILE1, EXP3CHAR, msg, EXPLNF1, EXPLN3))
			return 1;
	} 
	else if (!test_file_read(f, fn, exp, msg, maxlines))
		return 1;
	return 0;
}

char*
get_next_line_dummy(int fd) {
    char* line = NULL;
    char buffer[TESTBUFFSZ];
    
    // Read a line from the file descriptor
    ssize_t bytes_read = read(fd, buffer, TESTBUFFSZ);
    if (bytes_read > 0) {
        // Allocate memory for the line and copy the buffer content
        line = (char*)malloc(sizeof(char) * (bytes_read + 1)); // +1 for null terminator
        if (line != NULL) {
            memcpy(line, buffer, bytes_read);
            line[bytes_read] = '\0'; // Add null terminator
        } else {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
    } else if (bytes_read == -1) {
        perror("Read error");
        exit(EXIT_FAILURE);
    }
    
    return line;
}


void	print_processes()
{
	running_lg = process_is_running(EXNAMELG);
	running_sm = process_is_running(EXNAMESM);
	running_ex1 = process_is_running(EXNAME1);
	running_test = process_is_running("a.out");
    switch (running_lg << 2 | running_sm << 1 | running_ex1) {
        case 0b111:
            printf(YELLOW"log: All processes are running.\n"RESET);
            break;
        case 0b110:
            printf(YELLOW"log: " EXNAMELG" and "EXNAMESM" are running.\n"RESET);
            break;
        case 0b101:
            printf(YELLOW"log: " EXNAMELG" and "EXNAME1" are running.\n"RESET);
            break;
        case 0b011:
            printf(YELLOW"log: " EXNAMESM" and "EXNAME1" are running.\n"RESET);
            break;
        case 0b100:
            printf(YELLOW"log: "EXNAMELG" is running.\n"RESET);
            break;
        case 0b010:
            printf(YELLOW"log: "EXNAMESM" is running.\n"RESET);
            break;
        case 0b001:
            printf(YELLOW"log: "EXNAME1" is running.\n"RESET);
            break;
        default:
            printf(YELLOW"log: No processes are running.\n"RESET);
            break;
    }
}

static bool
tests_pass()
{
	int fails = 0;
	char command[200];
	int status = 0;
	char *(*f)(int) __attribute__((unused)) = TESTFUNC;
	print_processes();

// Compilations
	if(!file_exists(EXNAMELG))
	{
		printf(YELLOW"Compiling with "VAR2INJ"=%d...\n"RESET, BUFFLG);
		sprintf(command, CC" -D"VAR2INJ"=%d "CFLAGS" "EXNAMELG" "THISPROG" "TESTPROG" -L. -lft", BUFFLG);
		status = system(command);
		if (status != 0) {
			perror("\nCompilation 1 failed\n");
   	     return false;
   		}
	}
	if(!file_exists(EXNAMESM))
	{
		printf(YELLOW"Compiling with "VAR2INJ"=%d...\n"RESET, BUFFSM);
		sprintf(command, CC" -D"VAR2INJ"=%d "CFLAGS" "EXNAMESM" "THISPROG" "TESTPROG" -L. -lft", BUFFSM);
		status = system(command);
		if (status != 0) {
			perror("\nCompilation 1 failed\n");
   	     return false;
   		}
	}
	if(!file_exists(EXNAME1))
	{
		printf(YELLOW"Compiling with "VAR2INJ"=1...\n"RESET);
		sprintf(command, CC" -D"VAR2INJ"=1 "CFLAGS" "EXNAME1" "THISPROG" "TESTPROG" -L. -lft");
		status = system(command);
		if (status != 0) {
			perror("\nCompilation 1 failed\n");
   	     return false;
   		}
	}

#ifdef BUFFER_SIZE 
	#if BUFFER_SIZE == 1
		printf("Testing buffer=1\n");fflush(stdout);
		fails+=test(f, FILE1, EXPFILE1, MSG3, EXPLNF1); 		/* Size 1 buffer */
		printf("Buffer=1 tests finished.\n");fflush(stdout);
	#elif BUFFER_SIZE == BUFFSM
		printf("Testing buffer=%d\n", BUFFSM);fflush(stdout);
		fails+=test(f, FILE1,		EXPFILE1,	MSG2, EXPLNF1); 		/* Small buffer */
		fails+=test(f, CHAR3FILE,	EXP3CHAR,	MSG4, EXPLN3); 	/* Buffer equal to line len */
		fails+=test(f, CHAR4FILE,	EXP4CHAR,	MSG5, EXPLN4); 	/* Offset of +1 */
		fails+=test(f, CHAR2FILE,	EXP2CHAR,	MSG6, EXPLN2);	/* Offset of -1 */
		fails+=test(f, DUMMYFILE,	EXPDUMMY, 	MSG7, 0); 			/* STDIN */
		fails+=test(f, FILE1,		EXPFILE1,	MSG8, EXPLNF1); 		/* Reading from file */
		fails+=test(f, FILE2K,		EXPFILE2K,	MSG9, EXPLN2K); 	/* Long line file */
		fails+=test(f, CHAR3FILE,	EXP3CHAR,	MSG10, EXPLN3); /* Short line file */
		fails+=test(f, EMPTYFILE,	EXPEMPTY,	MSG11, EXPLNEMP); /* Empty line file */
		fails+=test(f, MULTIFILE,	EXP3CHAR,	MSG12, EXPLN3); /* Multi file read */
		printf("Buffer=%d tests finished.\n", BUFFSM);fflush(stdout);
	#elif BUFFER_SIZE == BUFFLG
		printf("Testing buffer=%d\n", BUFFLG);fflush(stdout);
		fails+=test(f, FILE2K, EXPFILE2K, MSG1, EXPLN2K); 	/*Large buffer  */
		printf("Buffer=%d tests finished.\n", BUFFLG);fflush(stdout);
	#else
		if (running_lg || running_sm || running_ex1)
		{
			printf("Undefined BUFFER SIZE value\n");
		//	return (false);
		}
	#endif
#else
		printf("BUFFER_SIZE not defined.\n");
#endif

// execute compiled programs
	if(!file_exists(EXNAMELG".lock")) {
		create_lock_file(EXNAMELG);
		printf(YELLOW"log: locking & executing "EXNAMELG"\n"RESET); fflush(stdout);
		system("./"EXNAMELG); 
	}
	if(!file_exists(EXNAMESM".lock")) {
		create_lock_file(EXNAMESM);
		printf(YELLOW"log: locking & executing "EXNAMESM"\n"RESET); fflush(stdout);
		system("./"EXNAMESM); 
	}
	if(!file_exists(EXNAME1".lock")) {
		create_lock_file(EXNAME1);
		printf(YELLOW"log: locking & executing "EXNAME1"\n"RESET); fflush(stdout);
		system("./"EXNAME1); 
	}

	print_processes();
	if (!running_lg && !running_sm && !running_ex1){
		printf(RED"log: removing lg lock\n"RESET);fflush(stdout);	
		remove_lock_file(EXNAMELG);
	}
	if (!running_lg && !running_sm && !running_ex1){
		printf(RED"log: removing sm lock\n"RESET);fflush(stdout);
		remove_lock_file(EXNAMESM);
	}
	if (!running_lg && !running_sm && !running_ex1){
		printf(RED"log: removing 1 lock\n"RESET);fflush(stdout);
		remove_lock_file(EXNAME1);
	}
	printf(YELLOW"log: ending tests...\n"RESET);
	if (fails && (running_lg || running_sm || running_ex1))
		return (false);
	return true;
}

int
main(int argc, char *argv[])
{
	(void)argc;
	print_processes();
	if ((strcmp(argv[0], EXNAMELG) != 0 && 
		 strcmp(argv[0], EXNAMESM) != 0 && 
		 strcmp(argv[0], EXNAME1)  != 0) || (
		(running_lg && !file_exists(EXNAMELG".lock")) ||
		(running_sm && !file_exists(EXNAMESM".lock")) ||
		(running_ex1 && !file_exists(EXNAME1".lock")) )) 
	{ 
		printf(YELLOW"\nRunning Mandatory Buffer-%d tests..."RESET"\n", BUFFER_SIZE);

		if (tests_pass() == true)
			printf(GREEN"All BUFF-%d tests passed!"RESET"\n", BUFFER_SIZE);
		else
		{
			printf(RED"BUFF-%d Test(s) failed... boo hoo"RESET"\n", BUFFER_SIZE);
			return 1;
		}
		printf(YELLOW"Running Bonus Part tests...TODO"RESET"\n");
	}
	return 0;
}
