/* +++Date last modified: 05-Jul-1997 */

/*
**        A Pratt-Boyer-Moore string search, written by Jerry Coffin
**  sometime or other in 1991.  Removed from original program, and
**  (incorrectly) rewritten for separate, generic use in early 1992.
**  Corrected with help from Thad Smith, late March and early
**  April 1992...hopefully it's correct this time. Revised by Bob Stout.
**
**  This is hereby placed in the Public Domain by its author.
**
**  10/21/93 rdg  Fixed bug found by Jeff Dunlop
*/

#include <stddef.h>
#include <string.h>
#include <limits.h>
//#include "../bareBench.h"
#include "pulpino.h"
#include "int.h"
#include "timer.h"
#include "event.h"


static size_t table[UCHAR_MAX + 1];
static size_t len;
static char *findme;

/*
**  Call this with the string to locate to initialize the table
*/

void init_search(const char *string)
{
      size_t i;

      len = strlen(string);
      for (i = 0; i <= UCHAR_MAX; i++)                      /* rdg 10/93 */
            table[i] = len;
      for (i = 0; i < len; i++)
            table[(unsigned char)string[i]] = len - i - 1;
      findme = (char *)string;
}

/*
**  Call this with a buffer to search
*/

char *strsearch(const char *string)
{
      register size_t shift;
      register size_t pos = len - 1;
      char *here;
      size_t limit=strlen(string);

      while (pos < limit)
      {
            while( pos < limit &&
                  (shift = table[(unsigned char)string[pos]]) > 0)
            {
                  pos += shift;
            }
            if (0 == shift)
            {
                  if (0 == strncmp(findme,
                        here = (char *)&string[pos-len+1], len))
                  {
                        return(here);
                  }
                  else  pos++;
            }
      }
      return NULL;
}

#include <stdio.h>

int main()
{
   ECP = 0xFFFFFFFF;
   IER = 1 << 29;
   int_enable();


   TPRA = 0x0;
   TIRA = 0x0;
   TOCRA = 1200000; 
   TPRA = 0x1;

      char *here;
      char *find_strings[] = { "Kur",
"gent",
"lass",
"suns",
"for",
"xxx",
"long",
"have",
"where",
"xxxxxx",
"xxxxxx",
"pense",
"pow",
"xxxxx",
"Yo",
"and",
"faded",
"20",
"you",
"bac",
"an",
"way",
"possibili",
"an",
"fat",
"imag",
"th",
"wor",
"xxx",
"xxx",
"yo",
"bxx",
"wo",
"kind",
"4",
"idle",
"Do",
"scare",
"people",
"wit",
"xxx",
"xxx",
"Th",
"xxx",
"yourself",
"Forget",
"succeed",
"Kee",
"lov",
"yo",
"Stretc",
"what",
"life",
"kno",
"wha",
"xxx",
"xxx",
"40",
"Get",
"xxx",
"them",
"Maybe",
"may",
"you",
"the",
"your",
"congratulate",
"much",
"either",
"are",
"Enjoy",
"it",
"be",
"other",
"it",
"xxx",
"greatest",
"own",
"nowhere",
"room",
"you",
"beauty",
"feel",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"it",
"Northern",
"before",
"Accept",
"Politicians",
"get",
"size",
"reasonable",
"their",
"Dont",
"support",
"trust",
"spouse",
"one",
"too",
"time",
"careful",
"with",
"Dispensing",
"past",
"the",
"parts",
"more",
"me",
"gent",
"lass",
"suns",
"for",
"xxx",
"long",
"have",
"where",
"xxxxxx",
"xxxxxx",
"pense",
"pow",
"xxxxx",
"Yo",
"and",
"faded",
"20",
"you",
"bac",
"an",
"way",
"possibili",
"an",
"fat",
"imag",
"th",
"wor",
"xxx",
"xxx",
"yo",
"bxx",
"wo",
"kind",
"4",
"idle",
"Do",
"scare",
"people",
"wit",
"xxx",
"xxx",
"Th",
"xxx",
"yourself",
"Forget",
"succeed",
"Kee",
"lov",
"yo",
"Stretc",
"what",
"life",
"kno",
"wha",
"xxx",
"xxx",
"40",
"Get",
"xxx",
"them",
"Maybe",
"may",
"you",
"the",
"your",
"congratulate",
"much",
"either",
"are",
"Enjoy",
"it",
"be",
"other",
"it",
"xxx",
"greatest",
"own",
"nowhere",
"room",
"you",
"beauty",
"feel",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"xxx",
"it",
"Northern",
"before",
"Accept",
"Politicians",
"get",
"size",
"reasonable",
"their",
"Dont",
"support",
"trust",
"spouse",
"one",
"too",
"time",
"careful",
"with",
"Dispensing",
"past",
"the",
"parts",
"more",
"me",
"gent",
"lass",
"suns",
"for",
"xxx",
"long",
"have",
"where",
"xxxxxx",
"xxxxxx",
"pense",
"pow",
"xxxxx",
"Yo",
"and",
"faded",
"20",
"you",
"bac",
"an",
"way",
"possibili",
"an",
"fat",
"imag",
"th",
"wor",
"xxx",
"xxx",
"yo",
"bxx",
"wo",
"kind",
"4",
"idle",
"Do",
"scare",
"people",
"wit",
"xxx",
"xxx",
"Th",
NULL};
      char *search_strings[] = { "Kurt Vonneguts Commencement Address at",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen",
"MIT Ladies and gentlemen of",
"the class of 97 Wear",
"sunscreen If I could offer",
"you only one tip for",
"the future sunscreen would be",
"it The longterm benefits of",
"sunscreen have been proved by",
"scientists whereas the rest of",
"my advice has no basis",
"more reliable than my own meandering experience",
"I will dispense this advice",
"now Enjoy the power and beauty",
"of your youth Oh never mind",
"You will not understand the power",
"and beauty of your youth until theyve",
"faded But trust me in",
"20 years",
"youll look",
"back at photos of yourself",
"and recall in a",
"way you cant grasp now how much",
"possibility lay before you",
"and how fabulous you really looked You",
"are not as fat",
"as you imagine Dont worry about",
"the future Or",
"worry but know that worrying is as effective",
"as trying to solve an algebra equation",
"by chewing bubble gum The real troubles in",
"your life are apt to",
"be things that never crossed your",
"worried mind the",
"kind that blindside you at",
"4 pm on some",
"idle Tuesday",
"Do one thing every day that",
"scares you Sing Dont be reckless with other",
"peoples hearts Dont put up",
"with people who are reckless",
"with yours Floss Dont waste your time",
"on jealousy Sometimes youre ahead sometimes youre behind",
"The race is long and in",
"the end its only with",
"yourself Remember compliments you receive",
"Forget the insults If you",
"succeed in doing this tell me how",
"Keep your old",
"love letters Throw away",
"your old bank statements",
"Stretch Dont feel guilty if you dont know",
"what you want to do with your",
"life The most interesting people I",
"know didnt know at 22",
"what they wanted",
"to do with their lives Some of",
"the most interesting",
"40yearolds I know still dont",
"Get plenty of calcium",
"Be kind to your knees Youll miss",
"them when theyre gone",
"Maybe youll marry",
"maybe you wont Maybe youll have children maybe",
"you wont Maybe youll divorce at 40 maybe youll dance",
"the funky chicken on",
"your 75th wedding anniversary Whatever",
"you do dont congratulate yourself too",
"much or berate yourself",
"either Your choices are half chance So",
"are everybody elses",
"Enjoy your body Use",
"it every way you can Dont",
"be afraid of it or of what",
"other people think of",
"it Its",
"the",
"greatest instrument youll ever",
"own Dance even if you have",
"nowhere to do it but your living",
"room Read the directions even if",
"you dont follow them Do not read",
"beauty magazines They will only make you",
"feel ugly Get to know your parents You never",
"know when theyll be gone for good Be",
"nice to your siblings Theyre your",
"best link to your",
"past and the people most likely",
"to stick with you",
"in the future Understand that",
"friends come and go but",
"with a precious few you should hold",
"on Work hard to bridge",
"the gaps in geography and lifestyle",
"because the older",
"you get the more you need the",
"people who knew you when you",
"were young Live",
"in New York City once but leave before",
"it makes you hard Live in",
"Northern California once but leave",
"before it makes you soft Travel",
"Accept certain inalienable truths Prices will rise",
"Politicians will philander You too will",
"get old And when you do youll",
"fantasize that when you were young prices were",
"reasonable politicians were noble and children respected",
"their elders Respect your elders",
"Dont expect anyone else to",
"support you Maybe you have a",
"trust fund Maybe youll have a wealthy",
"spouse But you never know when either",
"one might run out Dont mess",
"too much with your hair or by the",
"time youre 40 it will look 85 Be",
"careful whose advice you buy but be patient",
"with those who supply it Advice is a",
"form of nostalgia Dispensing it is",
"a way of fishing the past from",
"the disposal wiping it off painting",
"over the ugly parts",
"and recycling it for more than its",
"worth But trust me on the sunscreen"
};
      int i;
      int y;

      for(y = 0; y < 1; ++y)
      {
      for (i = 0; find_strings[i]; i++)
      {
            init_search(find_strings[i]);
            here = strsearch(search_strings[i]);
            printf("\"%s\" is%s in \"%s\"", find_strings[i],
                  here ? "" : " not", search_strings[i]);
            if (here)
                  printf(" [\"%s\"]", here);
            printf("\n");
      }
      }
   // disable timer
   TPRA = 0x0;
   ECP = 0x1;
   int_disable();
for(int runs = 0; runs < 76; runs++) //226
ISR_TA_CMP();
      return 0;
}

void __attribute__((optimize("O0"))) ISR_TA_CMP(void) { 
 ICP = (1 << 29); 
static int i = 1048572; 
i += 4; 
 asm volatile ( 
 "mv	x5, %0\n" // should be x5 = i; 
"addi x7, x5, 1024\n"
"addi x7, x7, 1024\n"
"lw	x6, 0(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 0(x5)\n" // * i = a;
"lw	x6, 4(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 4(x5)\n" // * i = a;
"lw	x6, 8(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 8(x5)\n" // * i = a;
"lw	x6, 12(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 12(x5)\n" // * i = a;
"lw	x6, 16(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 16(x5)\n" // * i = a;
"lw	x6, 20(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 20(x5)\n" // * i = a;
"lw	x6, 24(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 24(x5)\n" // * i = a;
"lw	x6, 28(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 28(x5)\n" // * i = a;
"lw	x6, 32(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 32(x5)\n" // * i = a;
"lw	x6, 36(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 36(x5)\n" // * i = a;
"lw	x6, 40(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 40(x5)\n" // * i = a;
"lw	x6, 44(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 44(x5)\n" // * i = a;
"lw	x6, 48(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 48(x5)\n" // * i = a;
"lw	x6, 52(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 52(x5)\n" // * i = a;
"lw	x6, 56(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 56(x5)\n" // * i = a;
"lw	x6, 60(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 60(x5)\n" // * i = a;
"lw	x6, 64(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 64(x5)\n" // * i = a;
"lw	x6, 68(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 68(x5)\n" // * i = a;
"lw	x6, 72(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 72(x5)\n" // * i = a;
"lw	x6, 76(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 76(x5)\n" // * i = a;
"lw	x6, 80(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 80(x5)\n" // * i = a;
"lw	x6, 84(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 84(x5)\n" // * i = a;
"lw	x6, 88(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 88(x5)\n" // * i = a;
"lw	x6, 92(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 92(x5)\n" // * i = a;
"lw	x6, 96(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 96(x5)\n" // * i = a;
"lw	x6, 100(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 100(x5)\n" // * i = a;
"lw	x6, 104(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 104(x5)\n" // * i = a;
"lw	x6, 108(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 108(x5)\n" // * i = a;
"lw	x6, 112(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 112(x5)\n" // * i = a;
"lw	x6, 116(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 116(x5)\n" // * i = a;
"lw	x6, 120(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 120(x5)\n" // * i = a;
"lw	x6, 124(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 124(x5)\n" // * i = a;
"lw	x6, 128(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 128(x5)\n" // * i = a;
"lw	x6, 132(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 132(x5)\n" // * i = a;
"lw	x6, 136(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 136(x5)\n" // * i = a;
"lw	x6, 140(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 140(x5)\n" // * i = a;
"lw	x6, 144(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 144(x5)\n" // * i = a;
"lw	x6, 148(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 148(x5)\n" // * i = a;
"lw	x6, 152(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 152(x5)\n" // * i = a;
"lw	x6, 156(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 156(x5)\n" // * i = a;
"lw	x6, 160(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 160(x5)\n" // * i = a;
"lw	x6, 164(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 164(x5)\n" // * i = a;
"lw	x6, 168(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 168(x5)\n" // * i = a;
"lw	x6, 172(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 172(x5)\n" // * i = a;
"lw	x6, 176(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 176(x5)\n" // * i = a;
"lw	x6, 180(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 180(x5)\n" // * i = a;
"lw	x6, 184(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 184(x5)\n" // * i = a;
"lw	x6, 188(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 188(x5)\n" // * i = a;
"lw	x6, 192(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 192(x5)\n" // * i = a;
"lw	x6, 196(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 196(x5)\n" // * i = a;
"lw	x6, 200(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 200(x5)\n" // * i = a;
"lw	x6, 204(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 204(x5)\n" // * i = a;
"lw	x6, 208(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 208(x5)\n" // * i = a;
"lw	x6, 212(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 212(x5)\n" // * i = a;
"lw	x6, 216(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 216(x5)\n" // * i = a;
"lw	x6, 220(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 220(x5)\n" // * i = a;
"lw	x6, 224(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 224(x5)\n" // * i = a;
"lw	x6, 228(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 228(x5)\n" // * i = a;
"lw	x6, 232(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 232(x5)\n" // * i = a;
"lw	x6, 236(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 236(x5)\n" // * i = a;
"lw	x6, 240(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 240(x5)\n" // * i = a;
"lw	x6, 244(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 244(x5)\n" // * i = a;
"lw	x6, 248(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 248(x5)\n" // * i = a;
"lw	x6, 252(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 252(x5)\n" // * i = a;
"lw	x6, 256(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 256(x5)\n" // * i = a;
"lw	x6, 260(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 260(x5)\n" // * i = a;
"lw	x6, 264(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 264(x5)\n" // * i = a;
"lw	x6, 268(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 268(x5)\n" // * i = a;
"lw	x6, 272(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 272(x5)\n" // * i = a;
"lw	x6, 276(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 276(x5)\n" // * i = a;
"lw	x6, 280(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 280(x5)\n" // * i = a;
"lw	x6, 284(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 284(x5)\n" // * i = a;
"lw	x6, 288(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 288(x5)\n" // * i = a;
"lw	x6, 292(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 292(x5)\n" // * i = a;
"lw	x6, 296(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 296(x5)\n" // * i = a;
"lw	x6, 300(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 300(x5)\n" // * i = a;
"lw	x6, 304(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 304(x5)\n" // * i = a;
"lw	x6, 308(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 308(x5)\n" // * i = a;
"lw	x6, 312(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 312(x5)\n" // * i = a;
"lw	x6, 316(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 316(x5)\n" // * i = a;
"lw	x6, 320(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 320(x5)\n" // * i = a;
"lw	x6, 324(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 324(x5)\n" // * i = a;
"lw	x6, 328(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 328(x5)\n" // * i = a;
"lw	x6, 332(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 332(x5)\n" // * i = a;
"lw	x6, 336(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 336(x5)\n" // * i = a;
"lw	x6, 340(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 340(x5)\n" // * i = a;
"lw	x6, 344(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 344(x5)\n" // * i = a;
"lw	x6, 348(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 348(x5)\n" // * i = a;
"lw	x6, 352(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 352(x5)\n" // * i = a;
"lw	x6, 356(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 356(x5)\n" // * i = a;
"lw	x6, 360(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 360(x5)\n" // * i = a;
"lw	x6, 364(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 364(x5)\n" // * i = a;
"lw	x6, 368(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 368(x5)\n" // * i = a;
"lw	x6, 372(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 372(x5)\n" // * i = a;
"lw	x6, 376(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 376(x5)\n" // * i = a;
"lw	x6, 380(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 380(x5)\n" // * i = a;
"lw	x6, 384(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 384(x5)\n" // * i = a;
"lw	x6, 388(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 388(x5)\n" // * i = a;
"lw	x6, 392(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 392(x5)\n" // * i = a;
"lw	x6, 396(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 396(x5)\n" // * i = a;
"lw	x6, 400(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 400(x5)\n" // * i = a;
"lw	x6, 404(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 404(x5)\n" // * i = a;
"lw	x6, 408(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 408(x5)\n" // * i = a;
"lw	x6, 412(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 412(x5)\n" // * i = a;
"lw	x6, 416(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 416(x5)\n" // * i = a;
"lw	x6, 420(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 420(x5)\n" // * i = a;
"lw	x6, 424(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 424(x5)\n" // * i = a;
"lw	x6, 428(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 428(x5)\n" // * i = a;
"lw	x6, 432(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 432(x5)\n" // * i = a;
"lw	x6, 436(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 436(x5)\n" // * i = a;
"lw	x6, 440(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 440(x5)\n" // * i = a;
"lw	x6, 444(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 444(x5)\n" // * i = a;
"lw	x6, 448(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 448(x5)\n" // * i = a;
"lw	x6, 452(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 452(x5)\n" // * i = a;
"lw	x6, 456(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 456(x5)\n" // * i = a;
"lw	x6, 460(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 460(x5)\n" // * i = a;
"lw	x6, 464(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 464(x5)\n" // * i = a;
"lw	x6, 468(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 468(x5)\n" // * i = a;
"lw	x6, 472(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 472(x5)\n" // * i = a;
"lw	x6, 476(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 476(x5)\n" // * i = a;
"lw	x6, 480(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 480(x5)\n" // * i = a;
"lw	x6, 484(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 484(x5)\n" // * i = a;
"lw	x6, 488(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 488(x5)\n" // * i = a;
"lw	x6, 492(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 492(x5)\n" // * i = a;
"lw	x6, 496(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 496(x5)\n" // * i = a;
"lw	x6, 500(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 500(x5)\n" // * i = a;
"lw	x6, 504(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 504(x5)\n" // * i = a;
"lw	x6, 508(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 508(x5)\n" // * i = a;
"lw	x6, 512(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 512(x5)\n" // * i = a;
"lw	x6, 516(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 516(x5)\n" // * i = a;
"lw	x6, 520(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 520(x5)\n" // * i = a;
"lw	x6, 524(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 524(x5)\n" // * i = a;
"lw	x6, 528(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 528(x5)\n" // * i = a;
"lw	x6, 532(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 532(x5)\n" // * i = a;
"lw	x6, 536(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 536(x5)\n" // * i = a;
"lw	x6, 540(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 540(x5)\n" // * i = a;
"lw	x6, 544(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 544(x5)\n" // * i = a;
"lw	x6, 548(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 548(x5)\n" // * i = a;
"lw	x6, 552(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 552(x5)\n" // * i = a;
"lw	x6, 556(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 556(x5)\n" // * i = a;
"lw	x6, 560(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 560(x5)\n" // * i = a;
"lw	x6, 564(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 564(x5)\n" // * i = a;
"lw	x6, 568(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 568(x5)\n" // * i = a;
"lw	x6, 572(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 572(x5)\n" // * i = a;
"lw	x6, 576(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 576(x5)\n" // * i = a;
"lw	x6, 580(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 580(x5)\n" // * i = a;
"lw	x6, 584(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 584(x5)\n" // * i = a;
"lw	x6, 588(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 588(x5)\n" // * i = a;
"lw	x6, 592(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 592(x5)\n" // * i = a;
"lw	x6, 596(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 596(x5)\n" // * i = a;
"lw	x6, 600(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 600(x5)\n" // * i = a;
"lw	x6, 604(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 604(x5)\n" // * i = a;
"lw	x6, 608(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 608(x5)\n" // * i = a;
"lw	x6, 612(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 612(x5)\n" // * i = a;
"lw	x6, 616(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 616(x5)\n" // * i = a;
"lw	x6, 620(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 620(x5)\n" // * i = a;
"lw	x6, 624(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 624(x5)\n" // * i = a;
"lw	x6, 628(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 628(x5)\n" // * i = a;
"lw	x6, 632(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 632(x5)\n" // * i = a;
"lw	x6, 636(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 636(x5)\n" // * i = a;
"lw	x6, 640(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 640(x5)\n" // * i = a;
"lw	x6, 644(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 644(x5)\n" // * i = a;
"lw	x6, 648(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 648(x5)\n" // * i = a;
"lw	x6, 652(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 652(x5)\n" // * i = a;
"lw	x6, 656(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 656(x5)\n" // * i = a;
"lw	x6, 660(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 660(x5)\n" // * i = a;
"lw	x6, 664(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 664(x5)\n" // * i = a;
"lw	x6, 668(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 668(x5)\n" // * i = a;
"lw	x6, 672(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 672(x5)\n" // * i = a;
"lw	x6, 676(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 676(x5)\n" // * i = a;
"lw	x6, 680(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 680(x5)\n" // * i = a;
"lw	x6, 684(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 684(x5)\n" // * i = a;
"lw	x6, 688(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 688(x5)\n" // * i = a;
"lw	x6, 692(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 692(x5)\n" // * i = a;
"lw	x6, 696(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 696(x5)\n" // * i = a;
"lw	x6, 700(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 700(x5)\n" // * i = a;
"lw	x6, 704(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 704(x5)\n" // * i = a;
"lw	x6, 708(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 708(x5)\n" // * i = a;
"lw	x6, 712(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 712(x5)\n" // * i = a;
"lw	x6, 716(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 716(x5)\n" // * i = a;
"lw	x6, 720(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 720(x5)\n" // * i = a;
"lw	x6, 724(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 724(x5)\n" // * i = a;
"lw	x6, 728(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 728(x5)\n" // * i = a;
"lw	x6, 732(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 732(x5)\n" // * i = a;
"lw	x6, 736(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 736(x5)\n" // * i = a;
"lw	x6, 740(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 740(x5)\n" // * i = a;
"lw	x6, 744(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 744(x5)\n" // * i = a;
"lw	x6, 748(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 748(x5)\n" // * i = a;
"lw	x6, 752(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 752(x5)\n" // * i = a;
"lw	x6, 756(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 756(x5)\n" // * i = a;
"lw	x6, 760(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 760(x5)\n" // * i = a;
"lw	x6, 764(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 764(x5)\n" // * i = a;
"lw	x6, 768(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 768(x5)\n" // * i = a;
"lw	x6, 772(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 772(x5)\n" // * i = a;
"lw	x6, 776(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 776(x5)\n" // * i = a;
"lw	x6, 780(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 780(x5)\n" // * i = a;
"lw	x6, 784(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 784(x5)\n" // * i = a;
"lw	x6, 788(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 788(x5)\n" // * i = a;
"lw	x6, 792(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 792(x5)\n" // * i = a;
"lw	x6, 796(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 796(x5)\n" // * i = a;
"lw	x6, 800(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 800(x5)\n" // * i = a;
"lw	x6, 804(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 804(x5)\n" // * i = a;
"lw	x6, 808(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 808(x5)\n" // * i = a;
"lw	x6, 812(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 812(x5)\n" // * i = a;
"lw	x6, 816(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 816(x5)\n" // * i = a;
"lw	x6, 820(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 820(x5)\n" // * i = a;
"lw	x6, 824(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 824(x5)\n" // * i = a;
"lw	x6, 828(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 828(x5)\n" // * i = a;
"lw	x6, 832(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 832(x5)\n" // * i = a;
"lw	x6, 836(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 836(x5)\n" // * i = a;
"lw	x6, 840(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 840(x5)\n" // * i = a;
"lw	x6, 844(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 844(x5)\n" // * i = a;
"lw	x6, 848(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 848(x5)\n" // * i = a;
"lw	x6, 852(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 852(x5)\n" // * i = a;
"lw	x6, 856(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 856(x5)\n" // * i = a;
"lw	x6, 860(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 860(x5)\n" // * i = a;
"lw	x6, 864(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 864(x5)\n" // * i = a;
"lw	x6, 868(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 868(x5)\n" // * i = a;
"lw	x6, 872(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 872(x5)\n" // * i = a;
"lw	x6, 876(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 876(x5)\n" // * i = a;
"lw	x6, 880(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 880(x5)\n" // * i = a;
"lw	x6, 884(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 884(x5)\n" // * i = a;
"lw	x6, 888(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 888(x5)\n" // * i = a;
"lw	x6, 892(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 892(x5)\n" // * i = a;
"lw	x6, 896(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 896(x5)\n" // * i = a;
"lw	x6, 900(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 900(x5)\n" // * i = a;
"lw	x6, 904(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 904(x5)\n" // * i = a;
"lw	x6, 908(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 908(x5)\n" // * i = a;
"lw	x6, 912(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 912(x5)\n" // * i = a;
"lw	x6, 916(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 916(x5)\n" // * i = a;
"lw	x6, 920(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 920(x5)\n" // * i = a;
"lw	x6, 924(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 924(x5)\n" // * i = a;
"lw	x6, 928(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 928(x5)\n" // * i = a;
"lw	x6, 932(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 932(x5)\n" // * i = a;
"lw	x6, 936(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 936(x5)\n" // * i = a;
"lw	x6, 940(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 940(x5)\n" // * i = a;
"lw	x6, 944(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 944(x5)\n" // * i = a;
"lw	x6, 948(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 948(x5)\n" // * i = a;
"lw	x6, 952(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 952(x5)\n" // * i = a;
"lw	x6, 956(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 956(x5)\n" // * i = a;
"lw	x6, 960(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 960(x5)\n" // * i = a;
"lw	x6, 964(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 964(x5)\n" // * i = a;
"lw	x6, 968(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 968(x5)\n" // * i = a;
"lw	x6, 972(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 972(x5)\n" // * i = a;
"lw	x6, 976(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 976(x5)\n" // * i = a;
"lw	x6, 980(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 980(x5)\n" // * i = a;
"lw	x6, 984(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 984(x5)\n" // * i = a;
"lw	x6, 988(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 988(x5)\n" // * i = a;
"lw	x6, 992(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 992(x5)\n" // * i = a;
"lw	x6, 996(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 996(x5)\n" // * i = a;
"lw	x6, 1000(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1000(x5)\n" // * i = a;
"lw	x6, 1004(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1004(x5)\n" // * i = a;
"lw	x6, 1008(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1008(x5)\n" // * i = a;
"lw	x6, 1012(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1012(x5)\n" // * i = a;
"lw	x6, 1016(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1016(x5)\n" // * i = a;
"lw	x6, 1020(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1020(x5)\n" // * i = a;
"lw	x6, 1024(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1024(x5)\n" // * i = a;
"lw	x6, 1028(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1028(x5)\n" // * i = a;
"lw	x6, 1032(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1032(x5)\n" // * i = a;
"lw	x6, 1036(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1036(x5)\n" // * i = a;
"lw	x6, 1040(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1040(x5)\n" // * i = a;
"lw	x6, 1044(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1044(x5)\n" // * i = a;
"lw	x6, 1048(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1048(x5)\n" // * i = a;
"lw	x6, 1052(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1052(x5)\n" // * i = a;
"lw	x6, 1056(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1056(x5)\n" // * i = a;
"lw	x6, 1060(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1060(x5)\n" // * i = a;
"lw	x6, 1064(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1064(x5)\n" // * i = a;
"lw	x6, 1068(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1068(x5)\n" // * i = a;
"lw	x6, 1072(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1072(x5)\n" // * i = a;
"lw	x6, 1076(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1076(x5)\n" // * i = a;
"lw	x6, 1080(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1080(x5)\n" // * i = a;
"lw	x6, 1084(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1084(x5)\n" // * i = a;
"lw	x6, 1088(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1088(x5)\n" // * i = a;
"lw	x6, 1092(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1092(x5)\n" // * i = a;
"lw	x6, 1096(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1096(x5)\n" // * i = a;
"lw	x6, 1100(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1100(x5)\n" // * i = a;
"lw	x6, 1104(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1104(x5)\n" // * i = a;
"lw	x6, 1108(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1108(x5)\n" // * i = a;
"lw	x6, 1112(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1112(x5)\n" // * i = a;
"lw	x6, 1116(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1116(x5)\n" // * i = a;
"lw	x6, 1120(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1120(x5)\n" // * i = a;
"lw	x6, 1124(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1124(x5)\n" // * i = a;
"lw	x6, 1128(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1128(x5)\n" // * i = a;
"lw	x6, 1132(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1132(x5)\n" // * i = a;
"lw	x6, 1136(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1136(x5)\n" // * i = a;
"lw	x6, 1140(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1140(x5)\n" // * i = a;
"lw	x6, 1144(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1144(x5)\n" // * i = a;
"lw	x6, 1148(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1148(x5)\n" // * i = a;
"lw	x6, 1152(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1152(x5)\n" // * i = a;
"lw	x6, 1156(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1156(x5)\n" // * i = a;
"lw	x6, 1160(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1160(x5)\n" // * i = a;
"lw	x6, 1164(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1164(x5)\n" // * i = a;
"lw	x6, 1168(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1168(x5)\n" // * i = a;
"lw	x6, 1172(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1172(x5)\n" // * i = a;
"lw	x6, 1176(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1176(x5)\n" // * i = a;
"lw	x6, 1180(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1180(x5)\n" // * i = a;
"lw	x6, 1184(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1184(x5)\n" // * i = a;
"lw	x6, 1188(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1188(x5)\n" // * i = a;
"lw	x6, 1192(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1192(x5)\n" // * i = a;
"lw	x6, 1196(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1196(x5)\n" // * i = a;
"lw	x6, 1200(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1200(x5)\n" // * i = a;
"lw	x6, 1204(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1204(x5)\n" // * i = a;
"lw	x6, 1208(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1208(x5)\n" // * i = a;
"lw	x6, 1212(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1212(x5)\n" // * i = a;
"lw	x6, 1216(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1216(x5)\n" // * i = a;
"lw	x6, 1220(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1220(x5)\n" // * i = a;
"lw	x6, 1224(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1224(x5)\n" // * i = a;
"lw	x6, 1228(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1228(x5)\n" // * i = a;
"lw	x6, 1232(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1232(x5)\n" // * i = a;
"lw	x6, 1236(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1236(x5)\n" // * i = a;
"lw	x6, 1240(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1240(x5)\n" // * i = a;
"lw	x6, 1244(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1244(x5)\n" // * i = a;
"lw	x6, 1248(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1248(x5)\n" // * i = a;
"lw	x6, 1252(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1252(x5)\n" // * i = a;
"lw	x6, 1256(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1256(x5)\n" // * i = a;
"lw	x6, 1260(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1260(x5)\n" // * i = a;
"lw	x6, 1264(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1264(x5)\n" // * i = a;
"lw	x6, 1268(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1268(x5)\n" // * i = a;
"lw	x6, 1272(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1272(x5)\n" // * i = a;
"lw	x6, 1276(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1276(x5)\n" // * i = a;
"lw	x6, 1280(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1280(x5)\n" // * i = a;
"lw	x6, 1284(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1284(x5)\n" // * i = a;
"lw	x6, 1288(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1288(x5)\n" // * i = a;
"lw	x6, 1292(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1292(x5)\n" // * i = a;
"lw	x6, 1296(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1296(x5)\n" // * i = a;
"lw	x6, 1300(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1300(x5)\n" // * i = a;
"lw	x6, 1304(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1304(x5)\n" // * i = a;
"lw	x6, 1308(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1308(x5)\n" // * i = a;
"lw	x6, 1312(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1312(x5)\n" // * i = a;
"lw	x6, 1316(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1316(x5)\n" // * i = a;
"lw	x6, 1320(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1320(x5)\n" // * i = a;
"lw	x6, 1324(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1324(x5)\n" // * i = a;
"lw	x6, 1328(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1328(x5)\n" // * i = a;
"lw	x6, 1332(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1332(x5)\n" // * i = a;
"lw	x6, 1336(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1336(x5)\n" // * i = a;
"lw	x6, 1340(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1340(x5)\n" // * i = a;
"lw	x6, 1344(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1344(x5)\n" // * i = a;
"lw	x6, 1348(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1348(x5)\n" // * i = a;
"lw	x6, 1352(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1352(x5)\n" // * i = a;
"lw	x6, 1356(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1356(x5)\n" // * i = a;
"lw	x6, 1360(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1360(x5)\n" // * i = a;
"lw	x6, 1364(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1364(x5)\n" // * i = a;
"lw	x6, 1368(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1368(x5)\n" // * i = a;
"lw	x6, 1372(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1372(x5)\n" // * i = a;
"lw	x6, 1376(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1376(x5)\n" // * i = a;
"lw	x6, 1380(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1380(x5)\n" // * i = a;
"lw	x6, 1384(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1384(x5)\n" // * i = a;
"lw	x6, 1388(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1388(x5)\n" // * i = a;
"lw	x6, 1392(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1392(x5)\n" // * i = a;
"lw	x6, 1396(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1396(x5)\n" // * i = a;
"lw	x6, 1400(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1400(x5)\n" // * i = a;
"lw	x6, 1404(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1404(x5)\n" // * i = a;
"lw	x6, 1408(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1408(x5)\n" // * i = a;
"lw	x6, 1412(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1412(x5)\n" // * i = a;
"lw	x6, 1416(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1416(x5)\n" // * i = a;
"lw	x6, 1420(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1420(x5)\n" // * i = a;
"lw	x6, 1424(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1424(x5)\n" // * i = a;
"lw	x6, 1428(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1428(x5)\n" // * i = a;
"lw	x6, 1432(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1432(x5)\n" // * i = a;
"lw	x6, 1436(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1436(x5)\n" // * i = a;
"lw	x6, 1440(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1440(x5)\n" // * i = a;
"lw	x6, 1444(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1444(x5)\n" // * i = a;
"lw	x6, 1448(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1448(x5)\n" // * i = a;
"lw	x6, 1452(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1452(x5)\n" // * i = a;
"lw	x6, 1456(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1456(x5)\n" // * i = a;
"lw	x6, 1460(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1460(x5)\n" // * i = a;
"lw	x6, 1464(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1464(x5)\n" // * i = a;
"lw	x6, 1468(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1468(x5)\n" // * i = a;
"lw	x6, 1472(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1472(x5)\n" // * i = a;
"lw	x6, 1476(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1476(x5)\n" // * i = a;
"lw	x6, 1480(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1480(x5)\n" // * i = a;
"lw	x6, 1484(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1484(x5)\n" // * i = a;
"lw	x6, 1488(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1488(x5)\n" // * i = a;
"lw	x6, 1492(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1492(x5)\n" // * i = a;
"lw	x6, 1496(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1496(x5)\n" // * i = a;
"lw	x6, 1500(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1500(x5)\n" // * i = a;
"lw	x6, 1504(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1504(x5)\n" // * i = a;
"lw	x6, 1508(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1508(x5)\n" // * i = a;
"lw	x6, 1512(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1512(x5)\n" // * i = a;
"lw	x6, 1516(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1516(x5)\n" // * i = a;
"lw	x6, 1520(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1520(x5)\n" // * i = a;
"lw	x6, 1524(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1524(x5)\n" // * i = a;
"lw	x6, 1528(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1528(x5)\n" // * i = a;
"lw	x6, 1532(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1532(x5)\n" // * i = a;
"lw	x6, 1536(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1536(x5)\n" // * i = a;
"lw	x6, 1540(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1540(x5)\n" // * i = a;
"lw	x6, 1544(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1544(x5)\n" // * i = a;
"lw	x6, 1548(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1548(x5)\n" // * i = a;
"lw	x6, 1552(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1552(x5)\n" // * i = a;
"lw	x6, 1556(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1556(x5)\n" // * i = a;
"lw	x6, 1560(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1560(x5)\n" // * i = a;
"lw	x6, 1564(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1564(x5)\n" // * i = a;
"lw	x6, 1568(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1568(x5)\n" // * i = a;
"lw	x6, 1572(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1572(x5)\n" // * i = a;
"lw	x6, 1576(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1576(x5)\n" // * i = a;
"lw	x6, 1580(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1580(x5)\n" // * i = a;
"lw	x6, 1584(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1584(x5)\n" // * i = a;
"lw	x6, 1588(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1588(x5)\n" // * i = a;
"lw	x6, 1592(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1592(x5)\n" // * i = a;
"lw	x6, 1596(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1596(x5)\n" // * i = a;
"lw	x6, 1600(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1600(x5)\n" // * i = a;
"lw	x6, 1604(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1604(x5)\n" // * i = a;
"lw	x6, 1608(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1608(x5)\n" // * i = a;
"lw	x6, 1612(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1612(x5)\n" // * i = a;
"lw	x6, 1616(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1616(x5)\n" // * i = a;
"lw	x6, 1620(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1620(x5)\n" // * i = a;
"lw	x6, 1624(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1624(x5)\n" // * i = a;
"lw	x6, 1628(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1628(x5)\n" // * i = a;
"lw	x6, 1632(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1632(x5)\n" // * i = a;
"lw	x6, 1636(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1636(x5)\n" // * i = a;
"lw	x6, 1640(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1640(x5)\n" // * i = a;
"lw	x6, 1644(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1644(x5)\n" // * i = a;
"lw	x6, 1648(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1648(x5)\n" // * i = a;
"lw	x6, 1652(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1652(x5)\n" // * i = a;
"lw	x6, 1656(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1656(x5)\n" // * i = a;
"lw	x6, 1660(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1660(x5)\n" // * i = a;
"lw	x6, 1664(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1664(x5)\n" // * i = a;
"lw	x6, 1668(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1668(x5)\n" // * i = a;
"lw	x6, 1672(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1672(x5)\n" // * i = a;
"lw	x6, 1676(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1676(x5)\n" // * i = a;
"lw	x6, 1680(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1680(x5)\n" // * i = a;
"lw	x6, 1684(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1684(x5)\n" // * i = a;
"lw	x6, 1688(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1688(x5)\n" // * i = a;
"lw	x6, 1692(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1692(x5)\n" // * i = a;
"lw	x6, 1696(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1696(x5)\n" // * i = a;
"lw	x6, 1700(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1700(x5)\n" // * i = a;
"lw	x6, 1704(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1704(x5)\n" // * i = a;
"lw	x6, 1708(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1708(x5)\n" // * i = a;
"lw	x6, 1712(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1712(x5)\n" // * i = a;
"lw	x6, 1716(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1716(x5)\n" // * i = a;
"lw	x6, 1720(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1720(x5)\n" // * i = a;
"lw	x6, 1724(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1724(x5)\n" // * i = a;
"lw	x6, 1728(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1728(x5)\n" // * i = a;
"lw	x6, 1732(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1732(x5)\n" // * i = a;
"lw	x6, 1736(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1736(x5)\n" // * i = a;
"lw	x6, 1740(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1740(x5)\n" // * i = a;
"lw	x6, 1744(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1744(x5)\n" // * i = a;
"lw	x6, 1748(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1748(x5)\n" // * i = a;
"lw	x6, 1752(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1752(x5)\n" // * i = a;
"lw	x6, 1756(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1756(x5)\n" // * i = a;
"lw	x6, 1760(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1760(x5)\n" // * i = a;
"lw	x6, 1764(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1764(x5)\n" // * i = a;
"lw	x6, 1768(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1768(x5)\n" // * i = a;
"lw	x6, 1772(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1772(x5)\n" // * i = a;
"lw	x6, 1776(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1776(x5)\n" // * i = a;
"lw	x6, 1780(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1780(x5)\n" // * i = a;
"lw	x6, 1784(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1784(x5)\n" // * i = a;
"lw	x6, 1788(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1788(x5)\n" // * i = a;
"lw	x6, 1792(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1792(x5)\n" // * i = a;
"lw	x6, 1796(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1796(x5)\n" // * i = a;
"lw	x6, 1800(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1800(x5)\n" // * i = a;
"lw	x6, 1804(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1804(x5)\n" // * i = a;
"lw	x6, 1808(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1808(x5)\n" // * i = a;
"lw	x6, 1812(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1812(x5)\n" // * i = a;
"lw	x6, 1816(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1816(x5)\n" // * i = a;
"lw	x6, 1820(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1820(x5)\n" // * i = a;
"lw	x6, 1824(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1824(x5)\n" // * i = a;
"lw	x6, 1828(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1828(x5)\n" // * i = a;
"lw	x6, 1832(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1832(x5)\n" // * i = a;
"lw	x6, 1836(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1836(x5)\n" // * i = a;
"lw	x6, 1840(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1840(x5)\n" // * i = a;
"lw	x6, 1844(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1844(x5)\n" // * i = a;
"lw	x6, 1848(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1848(x5)\n" // * i = a;
"lw	x6, 1852(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1852(x5)\n" // * i = a;
"lw	x6, 1856(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1856(x5)\n" // * i = a;
"lw	x6, 1860(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1860(x5)\n" // * i = a;
"lw	x6, 1864(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1864(x5)\n" // * i = a;
"lw	x6, 1868(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1868(x5)\n" // * i = a;
"lw	x6, 1872(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1872(x5)\n" // * i = a;
"lw	x6, 1876(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1876(x5)\n" // * i = a;
"lw	x6, 1880(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1880(x5)\n" // * i = a;
"lw	x6, 1884(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1884(x5)\n" // * i = a;
"lw	x6, 1888(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1888(x5)\n" // * i = a;
"lw	x6, 1892(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1892(x5)\n" // * i = a;
"lw	x6, 1896(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1896(x5)\n" // * i = a;
"lw	x6, 1900(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1900(x5)\n" // * i = a;
"lw	x6, 1904(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1904(x5)\n" // * i = a;
"lw	x6, 1908(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1908(x5)\n" // * i = a;
"lw	x6, 1912(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1912(x5)\n" // * i = a;
"lw	x6, 1916(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1916(x5)\n" // * i = a;
"lw	x6, 1920(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1920(x5)\n" // * i = a;
"lw	x6, 1924(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1924(x5)\n" // * i = a;
"lw	x6, 1928(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1928(x5)\n" // * i = a;
"lw	x6, 1932(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1932(x5)\n" // * i = a;
"lw	x6, 1936(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1936(x5)\n" // * i = a;
"lw	x6, 1940(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1940(x5)\n" // * i = a;
"lw	x6, 1944(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1944(x5)\n" // * i = a;
"lw	x6, 1948(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1948(x5)\n" // * i = a;
"lw	x6, 1952(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1952(x5)\n" // * i = a;
"lw	x6, 1956(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1956(x5)\n" // * i = a;
"lw	x6, 1960(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1960(x5)\n" // * i = a;
"lw	x6, 1964(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1964(x5)\n" // * i = a;
"lw	x6, 1968(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1968(x5)\n" // * i = a;
"lw	x6, 1972(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1972(x5)\n" // * i = a;
"lw	x6, 1976(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1976(x5)\n" // * i = a;
"lw	x6, 1980(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1980(x5)\n" // * i = a;
"lw	x6, 1984(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1984(x5)\n" // * i = a;
"lw	x6, 1988(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1988(x5)\n" // * i = a;
"lw	x6, 1992(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1992(x5)\n" // * i = a;
"lw	x6, 1996(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1996(x5)\n" // * i = a;
"lw	x6, 2000(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2000(x5)\n" // * i = a;
"lw	x6, 2004(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2004(x5)\n" // * i = a;
"lw	x6, 2008(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2008(x5)\n" // * i = a;
"lw	x6, 2012(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2012(x5)\n" // * i = a;
"lw	x6, 2016(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2016(x5)\n" // * i = a;
"lw	x6, 2020(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2020(x5)\n" // * i = a;
"lw	x6, 2024(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2024(x5)\n" // * i = a;
"lw	x6, 2028(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2028(x5)\n" // * i = a;
"lw	x6, 2032(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2032(x5)\n" // * i = a;
"lw	x6, 2036(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2036(x5)\n" // * i = a;
"lw	x6, 2040(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2040(x5)\n" // * i = a;
"lw	x6, 2044(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2044(x5)\n" // * i = a;
"lw	x6, 0(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 0(x7)\n" // * i = a;
"lw	x6, 4(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 4(x7)\n" // * i = a;
"lw	x6, 8(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 8(x7)\n" // * i = a;
"lw	x6, 12(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 12(x7)\n" // * i = a;
"lw	x6, 16(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 16(x7)\n" // * i = a;
"lw	x6, 20(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 20(x7)\n" // * i = a;
"lw	x6, 24(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 24(x7)\n" // * i = a;
"lw	x6, 28(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 28(x7)\n" // * i = a;
"lw	x6, 32(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 32(x7)\n" // * i = a;
"lw	x6, 36(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 36(x7)\n" // * i = a;
"lw	x6, 40(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 40(x7)\n" // * i = a;
"lw	x6, 44(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 44(x7)\n" // * i = a;
"lw	x6, 48(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 48(x7)\n" // * i = a;
"lw	x6, 52(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 52(x7)\n" // * i = a;
"lw	x6, 56(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 56(x7)\n" // * i = a;
"lw	x6, 60(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 60(x7)\n" // * i = a;
"lw	x6, 64(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 64(x7)\n" // * i = a;
"lw	x6, 68(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 68(x7)\n" // * i = a;
"lw	x6, 72(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 72(x7)\n" // * i = a;
"lw	x6, 76(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 76(x7)\n" // * i = a;
"lw	x6, 80(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 80(x7)\n" // * i = a;
"lw	x6, 84(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 84(x7)\n" // * i = a;
"lw	x6, 88(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 88(x7)\n" // * i = a;
"lw	x6, 92(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 92(x7)\n" // * i = a;
"lw	x6, 96(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 96(x7)\n" // * i = a;
"lw	x6, 100(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 100(x7)\n" // * i = a;
"lw	x6, 104(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 104(x7)\n" // * i = a;
"lw	x6, 108(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 108(x7)\n" // * i = a;
"lw	x6, 112(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 112(x7)\n" // * i = a;
"lw	x6, 116(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 116(x7)\n" // * i = a;
"lw	x6, 120(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 120(x7)\n" // * i = a;
"lw	x6, 124(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 124(x7)\n" // * i = a;
"lw	x6, 128(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 128(x7)\n" // * i = a;
"lw	x6, 132(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 132(x7)\n" // * i = a;
"lw	x6, 136(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 136(x7)\n" // * i = a;
"lw	x6, 140(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 140(x7)\n" // * i = a;
"lw	x6, 144(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 144(x7)\n" // * i = a;
"lw	x6, 148(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 148(x7)\n" // * i = a;
"lw	x6, 152(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 152(x7)\n" // * i = a;
"lw	x6, 156(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 156(x7)\n" // * i = a;
"lw	x6, 160(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 160(x7)\n" // * i = a;
"lw	x6, 164(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 164(x7)\n" // * i = a;
"lw	x6, 168(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 168(x7)\n" // * i = a;
"lw	x6, 172(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 172(x7)\n" // * i = a;
"lw	x6, 176(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 176(x7)\n" // * i = a;
"lw	x6, 180(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 180(x7)\n" // * i = a;
"lw	x6, 184(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 184(x7)\n" // * i = a;
"lw	x6, 188(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 188(x7)\n" // * i = a;
"lw	x6, 192(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 192(x7)\n" // * i = a;
"lw	x6, 196(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 196(x7)\n" // * i = a;
"lw	x6, 200(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 200(x7)\n" // * i = a;
"lw	x6, 204(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 204(x7)\n" // * i = a;
"lw	x6, 208(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 208(x7)\n" // * i = a;
"lw	x6, 212(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 212(x7)\n" // * i = a;
"lw	x6, 216(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 216(x7)\n" // * i = a;
"lw	x6, 220(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 220(x7)\n" // * i = a;
"lw	x6, 224(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 224(x7)\n" // * i = a;
"lw	x6, 228(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 228(x7)\n" // * i = a;
"lw	x6, 232(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 232(x7)\n" // * i = a;
"lw	x6, 236(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 236(x7)\n" // * i = a;
"lw	x6, 240(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 240(x7)\n" // * i = a;
"lw	x6, 244(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 244(x7)\n" // * i = a;
"lw	x6, 248(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 248(x7)\n" // * i = a;
"lw	x6, 252(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 252(x7)\n" // * i = a;
"lw	x6, 256(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 256(x7)\n" // * i = a;
"lw	x6, 260(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 260(x7)\n" // * i = a;
"lw	x6, 264(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 264(x7)\n" // * i = a;
"lw	x6, 268(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 268(x7)\n" // * i = a;
"lw	x6, 272(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 272(x7)\n" // * i = a;
"lw	x6, 276(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 276(x7)\n" // * i = a;
"lw	x6, 280(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 280(x7)\n" // * i = a;
"lw	x6, 284(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 284(x7)\n" // * i = a;
"lw	x6, 288(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 288(x7)\n" // * i = a;
"lw	x6, 292(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 292(x7)\n" // * i = a;
"lw	x6, 296(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 296(x7)\n" // * i = a;
"lw	x6, 300(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 300(x7)\n" // * i = a;
"lw	x6, 304(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 304(x7)\n" // * i = a;
"lw	x6, 308(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 308(x7)\n" // * i = a;
"lw	x6, 312(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 312(x7)\n" // * i = a;
"lw	x6, 316(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 316(x7)\n" // * i = a;
"lw	x6, 320(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 320(x7)\n" // * i = a;
"lw	x6, 324(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 324(x7)\n" // * i = a;
"lw	x6, 328(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 328(x7)\n" // * i = a;
"lw	x6, 332(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 332(x7)\n" // * i = a;
"lw	x6, 336(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 336(x7)\n" // * i = a;
"lw	x6, 340(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 340(x7)\n" // * i = a;
"lw	x6, 344(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 344(x7)\n" // * i = a;
"lw	x6, 348(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 348(x7)\n" // * i = a;
"lw	x6, 352(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 352(x7)\n" // * i = a;
"lw	x6, 356(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 356(x7)\n" // * i = a;
"lw	x6, 360(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 360(x7)\n" // * i = a;
"lw	x6, 364(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 364(x7)\n" // * i = a;
"lw	x6, 368(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 368(x7)\n" // * i = a;
"lw	x6, 372(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 372(x7)\n" // * i = a;
"lw	x6, 376(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 376(x7)\n" // * i = a;
"lw	x6, 380(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 380(x7)\n" // * i = a;
"lw	x6, 384(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 384(x7)\n" // * i = a;
"lw	x6, 388(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 388(x7)\n" // * i = a;
"lw	x6, 392(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 392(x7)\n" // * i = a;
"lw	x6, 396(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 396(x7)\n" // * i = a;
"lw	x6, 400(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 400(x7)\n" // * i = a;
"lw	x6, 404(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 404(x7)\n" // * i = a;
"lw	x6, 408(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 408(x7)\n" // * i = a;
"lw	x6, 412(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 412(x7)\n" // * i = a;
"lw	x6, 416(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 416(x7)\n" // * i = a;
"lw	x6, 420(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 420(x7)\n" // * i = a;
"lw	x6, 424(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 424(x7)\n" // * i = a;
"lw	x6, 428(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 428(x7)\n" // * i = a;
"lw	x6, 432(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 432(x7)\n" // * i = a;
"lw	x6, 436(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 436(x7)\n" // * i = a;
"lw	x6, 440(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 440(x7)\n" // * i = a;
"lw	x6, 444(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 444(x7)\n" // * i = a;
"lw	x6, 448(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 448(x7)\n" // * i = a;
"lw	x6, 452(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 452(x7)\n" // * i = a;
"lw	x6, 456(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 456(x7)\n" // * i = a;
"lw	x6, 460(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 460(x7)\n" // * i = a;
"lw	x6, 464(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 464(x7)\n" // * i = a;
"lw	x6, 468(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 468(x7)\n" // * i = a;
"lw	x6, 472(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 472(x7)\n" // * i = a;
"lw	x6, 476(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 476(x7)\n" // * i = a;
"lw	x6, 480(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 480(x7)\n" // * i = a;
"lw	x6, 484(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 484(x7)\n" // * i = a;
"lw	x6, 488(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 488(x7)\n" // * i = a;
"lw	x6, 492(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 492(x7)\n" // * i = a;
"lw	x6, 496(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 496(x7)\n" // * i = a;
"lw	x6, 500(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 500(x7)\n" // * i = a;
"lw	x6, 504(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 504(x7)\n" // * i = a;
"lw	x6, 508(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 508(x7)\n" // * i = a;
"lw	x6, 512(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 512(x7)\n" // * i = a;
"lw	x6, 516(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 516(x7)\n" // * i = a;
"lw	x6, 520(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 520(x7)\n" // * i = a;
"lw	x6, 524(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 524(x7)\n" // * i = a;
"lw	x6, 528(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 528(x7)\n" // * i = a;
"lw	x6, 532(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 532(x7)\n" // * i = a;
"lw	x6, 536(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 536(x7)\n" // * i = a;
"lw	x6, 540(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 540(x7)\n" // * i = a;
"lw	x6, 544(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 544(x7)\n" // * i = a;
"lw	x6, 548(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 548(x7)\n" // * i = a;
"lw	x6, 552(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 552(x7)\n" // * i = a;
"lw	x6, 556(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 556(x7)\n" // * i = a;
"lw	x6, 560(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 560(x7)\n" // * i = a;
"lw	x6, 564(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 564(x7)\n" // * i = a;
"lw	x6, 568(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 568(x7)\n" // * i = a;
"lw	x6, 572(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 572(x7)\n" // * i = a;
"lw	x6, 576(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 576(x7)\n" // * i = a;
"lw	x6, 580(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 580(x7)\n" // * i = a;
"lw	x6, 584(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 584(x7)\n" // * i = a;
"lw	x6, 588(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 588(x7)\n" // * i = a;
"lw	x6, 592(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 592(x7)\n" // * i = a;
"lw	x6, 596(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 596(x7)\n" // * i = a;
"lw	x6, 600(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 600(x7)\n" // * i = a;
"lw	x6, 604(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 604(x7)\n" // * i = a;
"lw	x6, 608(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 608(x7)\n" // * i = a;
"lw	x6, 612(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 612(x7)\n" // * i = a;
"lw	x6, 616(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 616(x7)\n" // * i = a;
"lw	x6, 620(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 620(x7)\n" // * i = a;
"lw	x6, 624(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 624(x7)\n" // * i = a;
"lw	x6, 628(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 628(x7)\n" // * i = a;
"lw	x6, 632(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 632(x7)\n" // * i = a;
"lw	x6, 636(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 636(x7)\n" // * i = a;
"lw	x6, 640(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 640(x7)\n" // * i = a;
"lw	x6, 644(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 644(x7)\n" // * i = a;
"lw	x6, 648(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 648(x7)\n" // * i = a;
"lw	x6, 652(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 652(x7)\n" // * i = a;
"lw	x6, 656(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 656(x7)\n" // * i = a;
"lw	x6, 660(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 660(x7)\n" // * i = a;
"lw	x6, 664(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 664(x7)\n" // * i = a;
"lw	x6, 668(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 668(x7)\n" // * i = a;
"lw	x6, 672(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 672(x7)\n" // * i = a;
"lw	x6, 676(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 676(x7)\n" // * i = a;
"lw	x6, 680(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 680(x7)\n" // * i = a;
"lw	x6, 684(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 684(x7)\n" // * i = a;
"lw	x6, 688(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 688(x7)\n" // * i = a;
"lw	x6, 692(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 692(x7)\n" // * i = a;
"lw	x6, 696(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 696(x7)\n" // * i = a;
"lw	x6, 700(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 700(x7)\n" // * i = a;
"lw	x6, 704(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 704(x7)\n" // * i = a;
"lw	x6, 708(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 708(x7)\n" // * i = a;
"lw	x6, 712(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 712(x7)\n" // * i = a;
"lw	x6, 716(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 716(x7)\n" // * i = a;
"lw	x6, 720(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 720(x7)\n" // * i = a;
"lw	x6, 724(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 724(x7)\n" // * i = a;
"lw	x6, 728(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 728(x7)\n" // * i = a;
"lw	x6, 732(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 732(x7)\n" // * i = a;
"lw	x6, 736(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 736(x7)\n" // * i = a;
"lw	x6, 740(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 740(x7)\n" // * i = a;
"lw	x6, 744(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 744(x7)\n" // * i = a;
"lw	x6, 748(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 748(x7)\n" // * i = a;
"lw	x6, 752(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 752(x7)\n" // * i = a;
"lw	x6, 756(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 756(x7)\n" // * i = a;
"lw	x6, 760(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 760(x7)\n" // * i = a;
"lw	x6, 764(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 764(x7)\n" // * i = a;
"lw	x6, 768(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 768(x7)\n" // * i = a;
"lw	x6, 772(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 772(x7)\n" // * i = a;
"lw	x6, 776(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 776(x7)\n" // * i = a;
"lw	x6, 780(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 780(x7)\n" // * i = a;
"lw	x6, 784(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 784(x7)\n" // * i = a;
"lw	x6, 788(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 788(x7)\n" // * i = a;
"lw	x6, 792(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 792(x7)\n" // * i = a;
"lw	x6, 796(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 796(x7)\n" // * i = a;
"lw	x6, 800(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 800(x7)\n" // * i = a;
"lw	x6, 804(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 804(x7)\n" // * i = a;
"lw	x6, 808(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 808(x7)\n" // * i = a;
"lw	x6, 812(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 812(x7)\n" // * i = a;
"lw	x6, 816(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 816(x7)\n" // * i = a;
"lw	x6, 820(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 820(x7)\n" // * i = a;
"lw	x6, 824(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 824(x7)\n" // * i = a;
"lw	x6, 828(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 828(x7)\n" // * i = a;
"lw	x6, 832(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 832(x7)\n" // * i = a;
"lw	x6, 836(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 836(x7)\n" // * i = a;
"lw	x6, 840(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 840(x7)\n" // * i = a;
"lw	x6, 844(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 844(x7)\n" // * i = a;
"lw	x6, 848(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 848(x7)\n" // * i = a;
"lw	x6, 852(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 852(x7)\n" // * i = a;
"lw	x6, 856(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 856(x7)\n" // * i = a;
"lw	x6, 860(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 860(x7)\n" // * i = a;
"lw	x6, 864(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 864(x7)\n" // * i = a;
"lw	x6, 868(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 868(x7)\n" // * i = a;
"lw	x6, 872(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 872(x7)\n" // * i = a;
"lw	x6, 876(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 876(x7)\n" // * i = a;
"lw	x6, 880(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 880(x7)\n" // * i = a;
"lw	x6, 884(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 884(x7)\n" // * i = a;
"lw	x6, 888(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 888(x7)\n" // * i = a;
"lw	x6, 892(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 892(x7)\n" // * i = a;
"lw	x6, 896(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 896(x7)\n" // * i = a;
"lw	x6, 900(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 900(x7)\n" // * i = a;
"lw	x6, 904(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 904(x7)\n" // * i = a;
"lw	x6, 908(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 908(x7)\n" // * i = a;
"lw	x6, 912(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 912(x7)\n" // * i = a;
"lw	x6, 916(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 916(x7)\n" // * i = a;
"lw	x6, 920(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 920(x7)\n" // * i = a;
"lw	x6, 924(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 924(x7)\n" // * i = a;
"lw	x6, 928(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 928(x7)\n" // * i = a;
"lw	x6, 932(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 932(x7)\n" // * i = a;
"lw	x6, 936(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 936(x7)\n" // * i = a;
"lw	x6, 940(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 940(x7)\n" // * i = a;
"lw	x6, 944(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 944(x7)\n" // * i = a;
"lw	x6, 948(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 948(x7)\n" // * i = a;
"lw	x6, 952(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 952(x7)\n" // * i = a;
"lw	x6, 956(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 956(x7)\n" // * i = a;
"lw	x6, 960(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 960(x7)\n" // * i = a;
"lw	x6, 964(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 964(x7)\n" // * i = a;
"lw	x6, 968(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 968(x7)\n" // * i = a;
"lw	x6, 972(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 972(x7)\n" // * i = a;
"lw	x6, 976(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 976(x7)\n" // * i = a;
"lw	x6, 980(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 980(x7)\n" // * i = a;
"lw	x6, 984(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 984(x7)\n" // * i = a;
"lw	x6, 988(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 988(x7)\n" // * i = a;
"lw	x6, 992(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 992(x7)\n" // * i = a;
"lw	x6, 996(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 996(x7)\n" // * i = a;
"lw	x6, 1000(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1000(x7)\n" // * i = a;
"lw	x6, 1004(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1004(x7)\n" // * i = a;
"lw	x6, 1008(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1008(x7)\n" // * i = a;
"lw	x6, 1012(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1012(x7)\n" // * i = a;
"lw	x6, 1016(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1016(x7)\n" // * i = a;
"lw	x6, 1020(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1020(x7)\n" // * i = a;
"lw	x6, 1024(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1024(x7)\n" // * i = a;
"lw	x6, 1028(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1028(x7)\n" // * i = a;
"lw	x6, 1032(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1032(x7)\n" // * i = a;
"lw	x6, 1036(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1036(x7)\n" // * i = a;
"lw	x6, 1040(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1040(x7)\n" // * i = a;
"lw	x6, 1044(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1044(x7)\n" // * i = a;
"lw	x6, 1048(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1048(x7)\n" // * i = a;
"lw	x6, 1052(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1052(x7)\n" // * i = a;
"lw	x6, 1056(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1056(x7)\n" // * i = a;
"lw	x6, 1060(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1060(x7)\n" // * i = a;
"lw	x6, 1064(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1064(x7)\n" // * i = a;
"lw	x6, 1068(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1068(x7)\n" // * i = a;
"lw	x6, 1072(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1072(x7)\n" // * i = a;
"lw	x6, 1076(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1076(x7)\n" // * i = a;
"lw	x6, 1080(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1080(x7)\n" // * i = a;
"lw	x6, 1084(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1084(x7)\n" // * i = a;
"lw	x6, 1088(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1088(x7)\n" // * i = a;
"lw	x6, 1092(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1092(x7)\n" // * i = a;
"lw	x6, 1096(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1096(x7)\n" // * i = a;
"lw	x6, 1100(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1100(x7)\n" // * i = a;
"lw	x6, 1104(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1104(x7)\n" // * i = a;
"lw	x6, 1108(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1108(x7)\n" // * i = a;
"lw	x6, 1112(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1112(x7)\n" // * i = a;
"lw	x6, 1116(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1116(x7)\n" // * i = a;
"lw	x6, 1120(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1120(x7)\n" // * i = a;
"lw	x6, 1124(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1124(x7)\n" // * i = a;
"lw	x6, 1128(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1128(x7)\n" // * i = a;
"lw	x6, 1132(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1132(x7)\n" // * i = a;
"lw	x6, 1136(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1136(x7)\n" // * i = a;
"lw	x6, 1140(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1140(x7)\n" // * i = a;
"lw	x6, 1144(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1144(x7)\n" // * i = a;
"lw	x6, 1148(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1148(x7)\n" // * i = a;
"lw	x6, 1152(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1152(x7)\n" // * i = a;
"lw	x6, 1156(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1156(x7)\n" // * i = a;
"lw	x6, 1160(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1160(x7)\n" // * i = a;
"lw	x6, 1164(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1164(x7)\n" // * i = a;
"lw	x6, 1168(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1168(x7)\n" // * i = a;
"lw	x6, 1172(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1172(x7)\n" // * i = a;
"lw	x6, 1176(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1176(x7)\n" // * i = a;
"lw	x6, 1180(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1180(x7)\n" // * i = a;
"lw	x6, 1184(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1184(x7)\n" // * i = a;
"lw	x6, 1188(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1188(x7)\n" // * i = a;
"lw	x6, 1192(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1192(x7)\n" // * i = a;
"lw	x6, 1196(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1196(x7)\n" // * i = a;
"lw	x6, 1200(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1200(x7)\n" // * i = a;
"lw	x6, 1204(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1204(x7)\n" // * i = a;
"lw	x6, 1208(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1208(x7)\n" // * i = a;
"lw	x6, 1212(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1212(x7)\n" // * i = a;
"lw	x6, 1216(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1216(x7)\n" // * i = a;
"lw	x6, 1220(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1220(x7)\n" // * i = a;
"lw	x6, 1224(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1224(x7)\n" // * i = a;
"lw	x6, 1228(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1228(x7)\n" // * i = a;
"lw	x6, 1232(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1232(x7)\n" // * i = a;
"lw	x6, 1236(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1236(x7)\n" // * i = a;
"lw	x6, 1240(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1240(x7)\n" // * i = a;
"lw	x6, 1244(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1244(x7)\n" // * i = a;
"lw	x6, 1248(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1248(x7)\n" // * i = a;
"lw	x6, 1252(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1252(x7)\n" // * i = a;
"lw	x6, 1256(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1256(x7)\n" // * i = a;
"lw	x6, 1260(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1260(x7)\n" // * i = a;
"lw	x6, 1264(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1264(x7)\n" // * i = a;
"lw	x6, 1268(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1268(x7)\n" // * i = a;
"lw	x6, 1272(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1272(x7)\n" // * i = a;
"lw	x6, 1276(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1276(x7)\n" // * i = a;
"lw	x6, 1280(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1280(x7)\n" // * i = a;
"lw	x6, 1284(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1284(x7)\n" // * i = a;
"lw	x6, 1288(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1288(x7)\n" // * i = a;
"lw	x6, 1292(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1292(x7)\n" // * i = a;
"lw	x6, 1296(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1296(x7)\n" // * i = a;
"lw	x6, 1300(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1300(x7)\n" // * i = a;
"lw	x6, 1304(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1304(x7)\n" // * i = a;
"lw	x6, 1308(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1308(x7)\n" // * i = a;
"lw	x6, 1312(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1312(x7)\n" // * i = a;
"lw	x6, 1316(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1316(x7)\n" // * i = a;
"lw	x6, 1320(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1320(x7)\n" // * i = a;
"lw	x6, 1324(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1324(x7)\n" // * i = a;
"lw	x6, 1328(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1328(x7)\n" // * i = a;
"lw	x6, 1332(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1332(x7)\n" // * i = a;
"lw	x6, 1336(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1336(x7)\n" // * i = a;
"lw	x6, 1340(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1340(x7)\n" // * i = a;
"lw	x6, 1344(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1344(x7)\n" // * i = a;
"lw	x6, 1348(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1348(x7)\n" // * i = a;
"lw	x6, 1352(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1352(x7)\n" // * i = a;
"lw	x6, 1356(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1356(x7)\n" // * i = a;
"lw	x6, 1360(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1360(x7)\n" // * i = a;
"lw	x6, 1364(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1364(x7)\n" // * i = a;
"lw	x6, 1368(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1368(x7)\n" // * i = a;
"lw	x6, 1372(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1372(x7)\n" // * i = a;
"lw	x6, 1376(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1376(x7)\n" // * i = a;
"lw	x6, 1380(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1380(x7)\n" // * i = a;
"lw	x6, 1384(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1384(x7)\n" // * i = a;
"lw	x6, 1388(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1388(x7)\n" // * i = a;
"lw	x6, 1392(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1392(x7)\n" // * i = a;
"lw	x6, 1396(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1396(x7)\n" // * i = a;
"lw	x6, 1400(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1400(x7)\n" // * i = a;
"lw	x6, 1404(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1404(x7)\n" // * i = a;
"lw	x6, 1408(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1408(x7)\n" // * i = a;
"lw	x6, 1412(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1412(x7)\n" // * i = a;
"lw	x6, 1416(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1416(x7)\n" // * i = a;
"lw	x6, 1420(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1420(x7)\n" // * i = a;
"lw	x6, 1424(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1424(x7)\n" // * i = a;
"lw	x6, 1428(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1428(x7)\n" // * i = a;
"lw	x6, 1432(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1432(x7)\n" // * i = a;
"lw	x6, 1436(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1436(x7)\n" // * i = a;
"lw	x6, 1440(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1440(x7)\n" // * i = a;
"lw	x6, 1444(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1444(x7)\n" // * i = a;
"lw	x6, 1448(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1448(x7)\n" // * i = a;
"lw	x6, 1452(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1452(x7)\n" // * i = a;
"lw	x6, 1456(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1456(x7)\n" // * i = a;
"lw	x6, 1460(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1460(x7)\n" // * i = a;
"lw	x6, 1464(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1464(x7)\n" // * i = a;
"lw	x6, 1468(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1468(x7)\n" // * i = a;
"lw	x6, 1472(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1472(x7)\n" // * i = a;
"lw	x6, 1476(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1476(x7)\n" // * i = a;
"lw	x6, 1480(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1480(x7)\n" // * i = a;
"lw	x6, 1484(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1484(x7)\n" // * i = a;
"lw	x6, 1488(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1488(x7)\n" // * i = a;
"lw	x6, 1492(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1492(x7)\n" // * i = a;
"lw	x6, 1496(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1496(x7)\n" // * i = a;
"lw	x6, 1500(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1500(x7)\n" // * i = a;
"lw	x6, 1504(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1504(x7)\n" // * i = a;
"lw	x6, 1508(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1508(x7)\n" // * i = a;
"lw	x6, 1512(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1512(x7)\n" // * i = a;
"lw	x6, 1516(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1516(x7)\n" // * i = a;
"lw	x6, 1520(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1520(x7)\n" // * i = a;
"lw	x6, 1524(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1524(x7)\n" // * i = a;
"lw	x6, 1528(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1528(x7)\n" // * i = a;
"lw	x6, 1532(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1532(x7)\n" // * i = a;
"lw	x6, 1536(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1536(x7)\n" // * i = a;
"lw	x6, 1540(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1540(x7)\n" // * i = a;
"lw	x6, 1544(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1544(x7)\n" // * i = a;
"lw	x6, 1548(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1548(x7)\n" // * i = a;
"lw	x6, 1552(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1552(x7)\n" // * i = a;
"lw	x6, 1556(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1556(x7)\n" // * i = a;
"lw	x6, 1560(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1560(x7)\n" // * i = a;
"lw	x6, 1564(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1564(x7)\n" // * i = a;
"lw	x6, 1568(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1568(x7)\n" // * i = a;
"lw	x6, 1572(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1572(x7)\n" // * i = a;
"lw	x6, 1576(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1576(x7)\n" // * i = a;
"lw	x6, 1580(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1580(x7)\n" // * i = a;
"lw	x6, 1584(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1584(x7)\n" // * i = a;
"lw	x6, 1588(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1588(x7)\n" // * i = a;
"lw	x6, 1592(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1592(x7)\n" // * i = a;
"lw	x6, 1596(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1596(x7)\n" // * i = a;
"lw	x6, 1600(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1600(x7)\n" // * i = a;
"lw	x6, 1604(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1604(x7)\n" // * i = a;
"lw	x6, 1608(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1608(x7)\n" // * i = a;
"lw	x6, 1612(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1612(x7)\n" // * i = a;
"lw	x6, 1616(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1616(x7)\n" // * i = a;
"lw	x6, 1620(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1620(x7)\n" // * i = a;
"lw	x6, 1624(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1624(x7)\n" // * i = a;
"lw	x6, 1628(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1628(x7)\n" // * i = a;
"lw	x6, 1632(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1632(x7)\n" // * i = a;
"lw	x6, 1636(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1636(x7)\n" // * i = a;
"lw	x6, 1640(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1640(x7)\n" // * i = a;
"lw	x6, 1644(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1644(x7)\n" // * i = a;
"lw	x6, 1648(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1648(x7)\n" // * i = a;
"lw	x6, 1652(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1652(x7)\n" // * i = a;
"lw	x6, 1656(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1656(x7)\n" // * i = a;
"lw	x6, 1660(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1660(x7)\n" // * i = a;
"lw	x6, 1664(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1664(x7)\n" // * i = a;
"lw	x6, 1668(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1668(x7)\n" // * i = a;
"lw	x6, 1672(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1672(x7)\n" // * i = a;
"lw	x6, 1676(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1676(x7)\n" // * i = a;
"lw	x6, 1680(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1680(x7)\n" // * i = a;
"lw	x6, 1684(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1684(x7)\n" // * i = a;
"lw	x6, 1688(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1688(x7)\n" // * i = a;
"lw	x6, 1692(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1692(x7)\n" // * i = a;
"lw	x6, 1696(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1696(x7)\n" // * i = a;
"lw	x6, 1700(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1700(x7)\n" // * i = a;
"lw	x6, 1704(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1704(x7)\n" // * i = a;
"lw	x6, 1708(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1708(x7)\n" // * i = a;
"lw	x6, 1712(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1712(x7)\n" // * i = a;
"lw	x6, 1716(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1716(x7)\n" // * i = a;
"lw	x6, 1720(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1720(x7)\n" // * i = a;
"lw	x6, 1724(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1724(x7)\n" // * i = a;
"lw	x6, 1728(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1728(x7)\n" // * i = a;
"lw	x6, 1732(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1732(x7)\n" // * i = a;
"lw	x6, 1736(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1736(x7)\n" // * i = a;
"lw	x6, 1740(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1740(x7)\n" // * i = a;
"lw	x6, 1744(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1744(x7)\n" // * i = a;
"lw	x6, 1748(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1748(x7)\n" // * i = a;
"lw	x6, 1752(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1752(x7)\n" // * i = a;
"lw	x6, 1756(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1756(x7)\n" // * i = a;
"lw	x6, 1760(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1760(x7)\n" // * i = a;
"lw	x6, 1764(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1764(x7)\n" // * i = a;
"lw	x6, 1768(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1768(x7)\n" // * i = a;
"lw	x6, 1772(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1772(x7)\n" // * i = a;
"lw	x6, 1776(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1776(x7)\n" // * i = a;
"lw	x6, 1780(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1780(x7)\n" // * i = a;
"lw	x6, 1784(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1784(x7)\n" // * i = a;
"lw	x6, 1788(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1788(x7)\n" // * i = a;
"lw	x6, 1792(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1792(x7)\n" // * i = a;
"lw	x6, 1796(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1796(x7)\n" // * i = a;
"lw	x6, 1800(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1800(x7)\n" // * i = a;
"lw	x6, 1804(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1804(x7)\n" // * i = a;
"lw	x6, 1808(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1808(x7)\n" // * i = a;
"lw	x6, 1812(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1812(x7)\n" // * i = a;
"lw	x6, 1816(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1816(x7)\n" // * i = a;
"lw	x6, 1820(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1820(x7)\n" // * i = a;
"lw	x6, 1824(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1824(x7)\n" // * i = a;
"lw	x6, 1828(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1828(x7)\n" // * i = a;
"lw	x6, 1832(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1832(x7)\n" // * i = a;
"lw	x6, 1836(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1836(x7)\n" // * i = a;
"lw	x6, 1840(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1840(x7)\n" // * i = a;
"lw	x6, 1844(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1844(x7)\n" // * i = a;
"lw	x6, 1848(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1848(x7)\n" // * i = a;
"lw	x6, 1852(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1852(x7)\n" // * i = a;
"lw	x6, 1856(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1856(x7)\n" // * i = a;
"lw	x6, 1860(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1860(x7)\n" // * i = a;
"lw	x6, 1864(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1864(x7)\n" // * i = a;
"lw	x6, 1868(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1868(x7)\n" // * i = a;
"lw	x6, 1872(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1872(x7)\n" // * i = a;
"lw	x6, 1876(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1876(x7)\n" // * i = a;
"lw	x6, 1880(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1880(x7)\n" // * i = a;
"lw	x6, 1884(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1884(x7)\n" // * i = a;
"lw	x6, 1888(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1888(x7)\n" // * i = a;
"lw	x6, 1892(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1892(x7)\n" // * i = a;
"lw	x6, 1896(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1896(x7)\n" // * i = a;
"lw	x6, 1900(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1900(x7)\n" // * i = a;
"lw	x6, 1904(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1904(x7)\n" // * i = a;
"lw	x6, 1908(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1908(x7)\n" // * i = a;
"lw	x6, 1912(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1912(x7)\n" // * i = a;
"lw	x6, 1916(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1916(x7)\n" // * i = a;
"lw	x6, 1920(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1920(x7)\n" // * i = a;
"lw	x6, 1924(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1924(x7)\n" // * i = a;
"lw	x6, 1928(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1928(x7)\n" // * i = a;
"lw	x6, 1932(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1932(x7)\n" // * i = a;
"lw	x6, 1936(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1936(x7)\n" // * i = a;
"lw	x6, 1940(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1940(x7)\n" // * i = a;
"lw	x6, 1944(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1944(x7)\n" // * i = a;
"lw	x6, 1948(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1948(x7)\n" // * i = a;
"lw	x6, 1952(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1952(x7)\n" // * i = a;
"lw	x6, 1956(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1956(x7)\n" // * i = a;
"lw	x6, 1960(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1960(x7)\n" // * i = a;
"lw	x6, 1964(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1964(x7)\n" // * i = a;
"lw	x6, 1968(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1968(x7)\n" // * i = a;
"lw	x6, 1972(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1972(x7)\n" // * i = a;
"lw	x6, 1976(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1976(x7)\n" // * i = a;
"lw	x6, 1980(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1980(x7)\n" // * i = a;
"lw	x6, 1984(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1984(x7)\n" // * i = a;
"lw	x6, 1988(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1988(x7)\n" // * i = a;
"lw	x6, 1992(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1992(x7)\n" // * i = a;
"lw	x6, 1996(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1996(x7)\n" // * i = a;
"lw	x6, 2000(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2000(x7)\n" // * i = a;
"lw	x6, 2004(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2004(x7)\n" // * i = a;
"lw	x6, 2008(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2008(x7)\n" // * i = a;
"lw	x6, 2012(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2012(x7)\n" // * i = a;
"lw	x6, 2016(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2016(x7)\n" // * i = a;
"lw	x6, 2020(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2020(x7)\n" // * i = a;
"lw	x6, 2024(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2024(x7)\n" // * i = a;
"lw	x6, 2028(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2028(x7)\n" // * i = a;
"lw	x6, 2032(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2032(x7)\n" // * i = a;
"lw	x6, 2036(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2036(x7)\n" // * i = a;
"lw	x6, 2040(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2040(x7)\n" // * i = a;
"lw	x6, 2044(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2044(x7)\n" // * i = a;
"lw	x6, 0(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 0(x5)\n" // * i = a;
"lw	x6, 4(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 4(x5)\n" // * i = a;
"lw	x6, 8(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 8(x5)\n" // * i = a;
"lw	x6, 12(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 12(x5)\n" // * i = a;
"lw	x6, 16(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 16(x5)\n" // * i = a;
"lw	x6, 20(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 20(x5)\n" // * i = a;
"lw	x6, 24(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 24(x5)\n" // * i = a;
"lw	x6, 28(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 28(x5)\n" // * i = a;
"lw	x6, 32(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 32(x5)\n" // * i = a;
"lw	x6, 36(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 36(x5)\n" // * i = a;
"lw	x6, 40(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 40(x5)\n" // * i = a;
"lw	x6, 44(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 44(x5)\n" // * i = a;
"lw	x6, 48(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 48(x5)\n" // * i = a;
"lw	x6, 52(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 52(x5)\n" // * i = a;
"lw	x6, 56(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 56(x5)\n" // * i = a;
"lw	x6, 60(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 60(x5)\n" // * i = a;
"lw	x6, 64(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 64(x5)\n" // * i = a;
"lw	x6, 68(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 68(x5)\n" // * i = a;
"lw	x6, 72(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 72(x5)\n" // * i = a;
"lw	x6, 76(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 76(x5)\n" // * i = a;
"lw	x6, 80(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 80(x5)\n" // * i = a;
"lw	x6, 84(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 84(x5)\n" // * i = a;
"lw	x6, 88(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 88(x5)\n" // * i = a;
"lw	x6, 92(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 92(x5)\n" // * i = a;
"lw	x6, 96(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 96(x5)\n" // * i = a;
"lw	x6, 100(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 100(x5)\n" // * i = a;
"lw	x6, 104(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 104(x5)\n" // * i = a;
"lw	x6, 108(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 108(x5)\n" // * i = a;
"lw	x6, 112(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 112(x5)\n" // * i = a;
"lw	x6, 116(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 116(x5)\n" // * i = a;
"lw	x6, 120(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 120(x5)\n" // * i = a;
"lw	x6, 124(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 124(x5)\n" // * i = a;
"lw	x6, 128(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 128(x5)\n" // * i = a;
"lw	x6, 132(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 132(x5)\n" // * i = a;
"lw	x6, 136(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 136(x5)\n" // * i = a;
"lw	x6, 140(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 140(x5)\n" // * i = a;
"lw	x6, 144(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 144(x5)\n" // * i = a;
"lw	x6, 148(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 148(x5)\n" // * i = a;
"lw	x6, 152(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 152(x5)\n" // * i = a;
"lw	x6, 156(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 156(x5)\n" // * i = a;
"lw	x6, 160(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 160(x5)\n" // * i = a;
"lw	x6, 164(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 164(x5)\n" // * i = a;
"lw	x6, 168(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 168(x5)\n" // * i = a;
"lw	x6, 172(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 172(x5)\n" // * i = a;
"lw	x6, 176(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 176(x5)\n" // * i = a;
"lw	x6, 180(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 180(x5)\n" // * i = a;
"lw	x6, 184(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 184(x5)\n" // * i = a;
"lw	x6, 188(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 188(x5)\n" // * i = a;
"lw	x6, 192(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 192(x5)\n" // * i = a;
"lw	x6, 196(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 196(x5)\n" // * i = a;
"lw	x6, 200(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 200(x5)\n" // * i = a;
"lw	x6, 204(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 204(x5)\n" // * i = a;
"lw	x6, 208(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 208(x5)\n" // * i = a;
"lw	x6, 212(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 212(x5)\n" // * i = a;
"lw	x6, 216(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 216(x5)\n" // * i = a;
"lw	x6, 220(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 220(x5)\n" // * i = a;
"lw	x6, 224(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 224(x5)\n" // * i = a;
"lw	x6, 228(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 228(x5)\n" // * i = a;
"lw	x6, 232(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 232(x5)\n" // * i = a;
"lw	x6, 236(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 236(x5)\n" // * i = a;
"lw	x6, 240(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 240(x5)\n" // * i = a;
"lw	x6, 244(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 244(x5)\n" // * i = a;
"lw	x6, 248(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 248(x5)\n" // * i = a;
"lw	x6, 252(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 252(x5)\n" // * i = a;
"lw	x6, 256(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 256(x5)\n" // * i = a;
"lw	x6, 260(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 260(x5)\n" // * i = a;
"lw	x6, 264(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 264(x5)\n" // * i = a;
"lw	x6, 268(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 268(x5)\n" // * i = a;
"lw	x6, 272(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 272(x5)\n" // * i = a;
"lw	x6, 276(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 276(x5)\n" // * i = a;
"lw	x6, 280(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 280(x5)\n" // * i = a;
"lw	x6, 284(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 284(x5)\n" // * i = a;
"lw	x6, 288(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 288(x5)\n" // * i = a;
"lw	x6, 292(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 292(x5)\n" // * i = a;
"lw	x6, 296(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 296(x5)\n" // * i = a;
"lw	x6, 300(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 300(x5)\n" // * i = a;
"lw	x6, 304(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 304(x5)\n" // * i = a;
"lw	x6, 308(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 308(x5)\n" // * i = a;
"lw	x6, 312(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 312(x5)\n" // * i = a;
"lw	x6, 316(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 316(x5)\n" // * i = a;
"lw	x6, 320(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 320(x5)\n" // * i = a;
"lw	x6, 324(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 324(x5)\n" // * i = a;
"lw	x6, 328(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 328(x5)\n" // * i = a;
"lw	x6, 332(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 332(x5)\n" // * i = a;
"lw	x6, 336(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 336(x5)\n" // * i = a;
"lw	x6, 340(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 340(x5)\n" // * i = a;
"lw	x6, 344(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 344(x5)\n" // * i = a;
"lw	x6, 348(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 348(x5)\n" // * i = a;
"lw	x6, 352(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 352(x5)\n" // * i = a;
"lw	x6, 356(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 356(x5)\n" // * i = a;
"lw	x6, 360(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 360(x5)\n" // * i = a;
"lw	x6, 364(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 364(x5)\n" // * i = a;
"lw	x6, 368(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 368(x5)\n" // * i = a;
"lw	x6, 372(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 372(x5)\n" // * i = a;
"lw	x6, 376(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 376(x5)\n" // * i = a;
"lw	x6, 380(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 380(x5)\n" // * i = a;
"lw	x6, 384(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 384(x5)\n" // * i = a;
"lw	x6, 388(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 388(x5)\n" // * i = a;
"lw	x6, 392(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 392(x5)\n" // * i = a;
"lw	x6, 396(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 396(x5)\n" // * i = a;
"lw	x6, 400(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 400(x5)\n" // * i = a;
"lw	x6, 404(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 404(x5)\n" // * i = a;
"lw	x6, 408(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 408(x5)\n" // * i = a;
"lw	x6, 412(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 412(x5)\n" // * i = a;
"lw	x6, 416(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 416(x5)\n" // * i = a;
"lw	x6, 420(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 420(x5)\n" // * i = a;
"lw	x6, 424(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 424(x5)\n" // * i = a;
"lw	x6, 428(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 428(x5)\n" // * i = a;
"lw	x6, 432(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 432(x5)\n" // * i = a;
"lw	x6, 436(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 436(x5)\n" // * i = a;
"lw	x6, 440(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 440(x5)\n" // * i = a;
"lw	x6, 444(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 444(x5)\n" // * i = a;
"lw	x6, 448(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 448(x5)\n" // * i = a;
"lw	x6, 452(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 452(x5)\n" // * i = a;
"lw	x6, 456(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 456(x5)\n" // * i = a;
"lw	x6, 460(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 460(x5)\n" // * i = a;
"lw	x6, 464(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 464(x5)\n" // * i = a;
"lw	x6, 468(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 468(x5)\n" // * i = a;
"lw	x6, 472(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 472(x5)\n" // * i = a;
"lw	x6, 476(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 476(x5)\n" // * i = a;
"lw	x6, 480(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 480(x5)\n" // * i = a;
"lw	x6, 484(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 484(x5)\n" // * i = a;
"lw	x6, 488(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 488(x5)\n" // * i = a;
"lw	x6, 492(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 492(x5)\n" // * i = a;
"lw	x6, 496(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 496(x5)\n" // * i = a;
"lw	x6, 500(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 500(x5)\n" // * i = a;
"lw	x6, 504(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 504(x5)\n" // * i = a;
"lw	x6, 508(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 508(x5)\n" // * i = a;
"lw	x6, 512(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 512(x5)\n" // * i = a;
"lw	x6, 516(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 516(x5)\n" // * i = a;
"lw	x6, 520(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 520(x5)\n" // * i = a;
"lw	x6, 524(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 524(x5)\n" // * i = a;
"lw	x6, 528(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 528(x5)\n" // * i = a;
"lw	x6, 532(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 532(x5)\n" // * i = a;
"lw	x6, 536(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 536(x5)\n" // * i = a;
"lw	x6, 540(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 540(x5)\n" // * i = a;
"lw	x6, 544(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 544(x5)\n" // * i = a;
"lw	x6, 548(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 548(x5)\n" // * i = a;
"lw	x6, 552(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 552(x5)\n" // * i = a;
"lw	x6, 556(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 556(x5)\n" // * i = a;
"lw	x6, 560(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 560(x5)\n" // * i = a;
"lw	x6, 564(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 564(x5)\n" // * i = a;
"lw	x6, 568(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 568(x5)\n" // * i = a;
"lw	x6, 572(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 572(x5)\n" // * i = a;
"lw	x6, 576(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 576(x5)\n" // * i = a;
"lw	x6, 580(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 580(x5)\n" // * i = a;
"lw	x6, 584(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 584(x5)\n" // * i = a;
"lw	x6, 588(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 588(x5)\n" // * i = a;
"lw	x6, 592(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 592(x5)\n" // * i = a;
"lw	x6, 596(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 596(x5)\n" // * i = a;
"lw	x6, 600(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 600(x5)\n" // * i = a;
"lw	x6, 604(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 604(x5)\n" // * i = a;
"lw	x6, 608(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 608(x5)\n" // * i = a;
"lw	x6, 612(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 612(x5)\n" // * i = a;
"lw	x6, 616(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 616(x5)\n" // * i = a;
"lw	x6, 620(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 620(x5)\n" // * i = a;
"lw	x6, 624(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 624(x5)\n" // * i = a;
"lw	x6, 628(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 628(x5)\n" // * i = a;
"lw	x6, 632(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 632(x5)\n" // * i = a;
"lw	x6, 636(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 636(x5)\n" // * i = a;
"lw	x6, 640(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 640(x5)\n" // * i = a;
"lw	x6, 644(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 644(x5)\n" // * i = a;
"lw	x6, 648(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 648(x5)\n" // * i = a;
"lw	x6, 652(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 652(x5)\n" // * i = a;
"lw	x6, 656(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 656(x5)\n" // * i = a;
"lw	x6, 660(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 660(x5)\n" // * i = a;
"lw	x6, 664(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 664(x5)\n" // * i = a;
"lw	x6, 668(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 668(x5)\n" // * i = a;
"lw	x6, 672(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 672(x5)\n" // * i = a;
"lw	x6, 676(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 676(x5)\n" // * i = a;
"lw	x6, 680(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 680(x5)\n" // * i = a;
"lw	x6, 684(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 684(x5)\n" // * i = a;
"lw	x6, 688(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 688(x5)\n" // * i = a;
"lw	x6, 692(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 692(x5)\n" // * i = a;
"lw	x6, 696(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 696(x5)\n" // * i = a;
"lw	x6, 700(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 700(x5)\n" // * i = a;
"lw	x6, 704(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 704(x5)\n" // * i = a;
"lw	x6, 708(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 708(x5)\n" // * i = a;
"lw	x6, 712(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 712(x5)\n" // * i = a;
"lw	x6, 716(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 716(x5)\n" // * i = a;
"lw	x6, 720(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 720(x5)\n" // * i = a;
"lw	x6, 724(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 724(x5)\n" // * i = a;
"lw	x6, 728(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 728(x5)\n" // * i = a;
"lw	x6, 732(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 732(x5)\n" // * i = a;
"lw	x6, 736(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 736(x5)\n" // * i = a;
"lw	x6, 740(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 740(x5)\n" // * i = a;
"lw	x6, 744(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 744(x5)\n" // * i = a;
"lw	x6, 748(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 748(x5)\n" // * i = a;
"lw	x6, 752(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 752(x5)\n" // * i = a;
"lw	x6, 756(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 756(x5)\n" // * i = a;
"lw	x6, 760(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 760(x5)\n" // * i = a;
"lw	x6, 764(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 764(x5)\n" // * i = a;
"lw	x6, 768(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 768(x5)\n" // * i = a;
"lw	x6, 772(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 772(x5)\n" // * i = a;
"lw	x6, 776(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 776(x5)\n" // * i = a;
"lw	x6, 780(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 780(x5)\n" // * i = a;
"lw	x6, 784(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 784(x5)\n" // * i = a;
"lw	x6, 788(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 788(x5)\n" // * i = a;
"lw	x6, 792(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 792(x5)\n" // * i = a;
"lw	x6, 796(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 796(x5)\n" // * i = a;
"lw	x6, 800(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 800(x5)\n" // * i = a;
"lw	x6, 804(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 804(x5)\n" // * i = a;
"lw	x6, 808(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 808(x5)\n" // * i = a;
"lw	x6, 812(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 812(x5)\n" // * i = a;
"lw	x6, 816(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 816(x5)\n" // * i = a;
"lw	x6, 820(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 820(x5)\n" // * i = a;
"lw	x6, 824(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 824(x5)\n" // * i = a;
"lw	x6, 828(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 828(x5)\n" // * i = a;
"lw	x6, 832(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 832(x5)\n" // * i = a;
"lw	x6, 836(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 836(x5)\n" // * i = a;
"lw	x6, 840(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 840(x5)\n" // * i = a;
"lw	x6, 844(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 844(x5)\n" // * i = a;
"lw	x6, 848(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 848(x5)\n" // * i = a;
"lw	x6, 852(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 852(x5)\n" // * i = a;
"lw	x6, 856(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 856(x5)\n" // * i = a;
"lw	x6, 860(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 860(x5)\n" // * i = a;
"lw	x6, 864(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 864(x5)\n" // * i = a;
"lw	x6, 868(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 868(x5)\n" // * i = a;
"lw	x6, 872(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 872(x5)\n" // * i = a;
"lw	x6, 876(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 876(x5)\n" // * i = a;
"lw	x6, 880(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 880(x5)\n" // * i = a;
"lw	x6, 884(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 884(x5)\n" // * i = a;
"lw	x6, 888(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 888(x5)\n" // * i = a;
"lw	x6, 892(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 892(x5)\n" // * i = a;
"lw	x6, 896(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 896(x5)\n" // * i = a;
"lw	x6, 900(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 900(x5)\n" // * i = a;
"lw	x6, 904(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 904(x5)\n" // * i = a;
"lw	x6, 908(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 908(x5)\n" // * i = a;
"lw	x6, 912(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 912(x5)\n" // * i = a;
"lw	x6, 916(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 916(x5)\n" // * i = a;
"lw	x6, 920(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 920(x5)\n" // * i = a;
"lw	x6, 924(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 924(x5)\n" // * i = a;
"lw	x6, 928(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 928(x5)\n" // * i = a;
"lw	x6, 932(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 932(x5)\n" // * i = a;
"lw	x6, 936(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 936(x5)\n" // * i = a;
"lw	x6, 940(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 940(x5)\n" // * i = a;
"lw	x6, 944(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 944(x5)\n" // * i = a;
"lw	x6, 948(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 948(x5)\n" // * i = a;
"lw	x6, 952(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 952(x5)\n" // * i = a;
"lw	x6, 956(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 956(x5)\n" // * i = a;
"lw	x6, 960(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 960(x5)\n" // * i = a;
"lw	x6, 964(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 964(x5)\n" // * i = a;
"lw	x6, 968(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 968(x5)\n" // * i = a;
"lw	x6, 972(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 972(x5)\n" // * i = a;
"lw	x6, 976(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 976(x5)\n" // * i = a;
"lw	x6, 980(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 980(x5)\n" // * i = a;
"lw	x6, 984(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 984(x5)\n" // * i = a;
"lw	x6, 988(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 988(x5)\n" // * i = a;
"lw	x6, 992(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 992(x5)\n" // * i = a;
"lw	x6, 996(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 996(x5)\n" // * i = a;
"lw	x6, 1000(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1000(x5)\n" // * i = a;
"lw	x6, 1004(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1004(x5)\n" // * i = a;
"lw	x6, 1008(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1008(x5)\n" // * i = a;
"lw	x6, 1012(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1012(x5)\n" // * i = a;
"lw	x6, 1016(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1016(x5)\n" // * i = a;
"lw	x6, 1020(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1020(x5)\n" // * i = a;
"lw	x6, 1024(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1024(x5)\n" // * i = a;
"lw	x6, 1028(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1028(x5)\n" // * i = a;
"lw	x6, 1032(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1032(x5)\n" // * i = a;
"lw	x6, 1036(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1036(x5)\n" // * i = a;
"lw	x6, 1040(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1040(x5)\n" // * i = a;
"lw	x6, 1044(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1044(x5)\n" // * i = a;
"lw	x6, 1048(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1048(x5)\n" // * i = a;
"lw	x6, 1052(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1052(x5)\n" // * i = a;
"lw	x6, 1056(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1056(x5)\n" // * i = a;
"lw	x6, 1060(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1060(x5)\n" // * i = a;
"lw	x6, 1064(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1064(x5)\n" // * i = a;
"lw	x6, 1068(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1068(x5)\n" // * i = a;
"lw	x6, 1072(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1072(x5)\n" // * i = a;
"lw	x6, 1076(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1076(x5)\n" // * i = a;
"lw	x6, 1080(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1080(x5)\n" // * i = a;
"lw	x6, 1084(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1084(x5)\n" // * i = a;
"lw	x6, 1088(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1088(x5)\n" // * i = a;
"lw	x6, 1092(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1092(x5)\n" // * i = a;
"lw	x6, 1096(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1096(x5)\n" // * i = a;
"lw	x6, 1100(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1100(x5)\n" // * i = a;
"lw	x6, 1104(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1104(x5)\n" // * i = a;
"lw	x6, 1108(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1108(x5)\n" // * i = a;
"lw	x6, 1112(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1112(x5)\n" // * i = a;
"lw	x6, 1116(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1116(x5)\n" // * i = a;
"lw	x6, 1120(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1120(x5)\n" // * i = a;
"lw	x6, 1124(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1124(x5)\n" // * i = a;
"lw	x6, 1128(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1128(x5)\n" // * i = a;
"lw	x6, 1132(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1132(x5)\n" // * i = a;
"lw	x6, 1136(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1136(x5)\n" // * i = a;
"lw	x6, 1140(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1140(x5)\n" // * i = a;
"lw	x6, 1144(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1144(x5)\n" // * i = a;
"lw	x6, 1148(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1148(x5)\n" // * i = a;
"lw	x6, 1152(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1152(x5)\n" // * i = a;
"lw	x6, 1156(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1156(x5)\n" // * i = a;
"lw	x6, 1160(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1160(x5)\n" // * i = a;
"lw	x6, 1164(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1164(x5)\n" // * i = a;
"lw	x6, 1168(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1168(x5)\n" // * i = a;
"lw	x6, 1172(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1172(x5)\n" // * i = a;
"lw	x6, 1176(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1176(x5)\n" // * i = a;
"lw	x6, 1180(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1180(x5)\n" // * i = a;
"lw	x6, 1184(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1184(x5)\n" // * i = a;
"lw	x6, 1188(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1188(x5)\n" // * i = a;
"lw	x6, 1192(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1192(x5)\n" // * i = a;
"lw	x6, 1196(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1196(x5)\n" // * i = a;
"lw	x6, 1200(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1200(x5)\n" // * i = a;
"lw	x6, 1204(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1204(x5)\n" // * i = a;
"lw	x6, 1208(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1208(x5)\n" // * i = a;
"lw	x6, 1212(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1212(x5)\n" // * i = a;
"lw	x6, 1216(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1216(x5)\n" // * i = a;
"lw	x6, 1220(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1220(x5)\n" // * i = a;
"lw	x6, 1224(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1224(x5)\n" // * i = a;
"lw	x6, 1228(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1228(x5)\n" // * i = a;
"lw	x6, 1232(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1232(x5)\n" // * i = a;
"lw	x6, 1236(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1236(x5)\n" // * i = a;
"lw	x6, 1240(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1240(x5)\n" // * i = a;
"lw	x6, 1244(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1244(x5)\n" // * i = a;
"lw	x6, 1248(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1248(x5)\n" // * i = a;
"lw	x6, 1252(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1252(x5)\n" // * i = a;
"lw	x6, 1256(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1256(x5)\n" // * i = a;
"lw	x6, 1260(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1260(x5)\n" // * i = a;
"lw	x6, 1264(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1264(x5)\n" // * i = a;
"lw	x6, 1268(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1268(x5)\n" // * i = a;
"lw	x6, 1272(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1272(x5)\n" // * i = a;
"lw	x6, 1276(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1276(x5)\n" // * i = a;
"lw	x6, 1280(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1280(x5)\n" // * i = a;
"lw	x6, 1284(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1284(x5)\n" // * i = a;
"lw	x6, 1288(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1288(x5)\n" // * i = a;
"lw	x6, 1292(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1292(x5)\n" // * i = a;
"lw	x6, 1296(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1296(x5)\n" // * i = a;
"lw	x6, 1300(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1300(x5)\n" // * i = a;
"lw	x6, 1304(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1304(x5)\n" // * i = a;
"lw	x6, 1308(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1308(x5)\n" // * i = a;
"lw	x6, 1312(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1312(x5)\n" // * i = a;
"lw	x6, 1316(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1316(x5)\n" // * i = a;
"lw	x6, 1320(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1320(x5)\n" // * i = a;
"lw	x6, 1324(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1324(x5)\n" // * i = a;
"lw	x6, 1328(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1328(x5)\n" // * i = a;
"lw	x6, 1332(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1332(x5)\n" // * i = a;
"lw	x6, 1336(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1336(x5)\n" // * i = a;
"lw	x6, 1340(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1340(x5)\n" // * i = a;
"lw	x6, 1344(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1344(x5)\n" // * i = a;
"lw	x6, 1348(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1348(x5)\n" // * i = a;
"lw	x6, 1352(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1352(x5)\n" // * i = a;
"lw	x6, 1356(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1356(x5)\n" // * i = a;
"lw	x6, 1360(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1360(x5)\n" // * i = a;
"lw	x6, 1364(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1364(x5)\n" // * i = a;
"lw	x6, 1368(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1368(x5)\n" // * i = a;
"lw	x6, 1372(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1372(x5)\n" // * i = a;
"lw	x6, 1376(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1376(x5)\n" // * i = a;
"lw	x6, 1380(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1380(x5)\n" // * i = a;
"lw	x6, 1384(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1384(x5)\n" // * i = a;
"lw	x6, 1388(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1388(x5)\n" // * i = a;
"lw	x6, 1392(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1392(x5)\n" // * i = a;
"lw	x6, 1396(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1396(x5)\n" // * i = a;
"lw	x6, 1400(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1400(x5)\n" // * i = a;
"lw	x6, 1404(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1404(x5)\n" // * i = a;
"lw	x6, 1408(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1408(x5)\n" // * i = a;
"lw	x6, 1412(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1412(x5)\n" // * i = a;
"lw	x6, 1416(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1416(x5)\n" // * i = a;
"lw	x6, 1420(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1420(x5)\n" // * i = a;
"lw	x6, 1424(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1424(x5)\n" // * i = a;
"lw	x6, 1428(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1428(x5)\n" // * i = a;
"lw	x6, 1432(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1432(x5)\n" // * i = a;
"lw	x6, 1436(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1436(x5)\n" // * i = a;
"lw	x6, 1440(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1440(x5)\n" // * i = a;
"lw	x6, 1444(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1444(x5)\n" // * i = a;
"lw	x6, 1448(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1448(x5)\n" // * i = a;
"lw	x6, 1452(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1452(x5)\n" // * i = a;
"lw	x6, 1456(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1456(x5)\n" // * i = a;
"lw	x6, 1460(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1460(x5)\n" // * i = a;
"lw	x6, 1464(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1464(x5)\n" // * i = a;
"lw	x6, 1468(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1468(x5)\n" // * i = a;
"lw	x6, 1472(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1472(x5)\n" // * i = a;
"lw	x6, 1476(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1476(x5)\n" // * i = a;
"lw	x6, 1480(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1480(x5)\n" // * i = a;
"lw	x6, 1484(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1484(x5)\n" // * i = a;
"lw	x6, 1488(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1488(x5)\n" // * i = a;
"lw	x6, 1492(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1492(x5)\n" // * i = a;
"lw	x6, 1496(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1496(x5)\n" // * i = a;
"lw	x6, 1500(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1500(x5)\n" // * i = a;
"lw	x6, 1504(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1504(x5)\n" // * i = a;
"lw	x6, 1508(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1508(x5)\n" // * i = a;
"lw	x6, 1512(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1512(x5)\n" // * i = a;
"lw	x6, 1516(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1516(x5)\n" // * i = a;
"lw	x6, 1520(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1520(x5)\n" // * i = a;
"lw	x6, 1524(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1524(x5)\n" // * i = a;
"lw	x6, 1528(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1528(x5)\n" // * i = a;
"lw	x6, 1532(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1532(x5)\n" // * i = a;
"lw	x6, 1536(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1536(x5)\n" // * i = a;
"lw	x6, 1540(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1540(x5)\n" // * i = a;
"lw	x6, 1544(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1544(x5)\n" // * i = a;
"lw	x6, 1548(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1548(x5)\n" // * i = a;
"lw	x6, 1552(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1552(x5)\n" // * i = a;
"lw	x6, 1556(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1556(x5)\n" // * i = a;
"lw	x6, 1560(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1560(x5)\n" // * i = a;
"lw	x6, 1564(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1564(x5)\n" // * i = a;
"lw	x6, 1568(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1568(x5)\n" // * i = a;
"lw	x6, 1572(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1572(x5)\n" // * i = a;
"lw	x6, 1576(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1576(x5)\n" // * i = a;
"lw	x6, 1580(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1580(x5)\n" // * i = a;
"lw	x6, 1584(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1584(x5)\n" // * i = a;
"lw	x6, 1588(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1588(x5)\n" // * i = a;
"lw	x6, 1592(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1592(x5)\n" // * i = a;
"lw	x6, 1596(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1596(x5)\n" // * i = a;
"lw	x6, 1600(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1600(x5)\n" // * i = a;
"lw	x6, 1604(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1604(x5)\n" // * i = a;
"lw	x6, 1608(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1608(x5)\n" // * i = a;
"lw	x6, 1612(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1612(x5)\n" // * i = a;
"lw	x6, 1616(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1616(x5)\n" // * i = a;
"lw	x6, 1620(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1620(x5)\n" // * i = a;
"lw	x6, 1624(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1624(x5)\n" // * i = a;
"lw	x6, 1628(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1628(x5)\n" // * i = a;
"lw	x6, 1632(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1632(x5)\n" // * i = a;
"lw	x6, 1636(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1636(x5)\n" // * i = a;
"lw	x6, 1640(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1640(x5)\n" // * i = a;
"lw	x6, 1644(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1644(x5)\n" // * i = a;
"lw	x6, 1648(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1648(x5)\n" // * i = a;
"lw	x6, 1652(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1652(x5)\n" // * i = a;
"lw	x6, 1656(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1656(x5)\n" // * i = a;
"lw	x6, 1660(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1660(x5)\n" // * i = a;
"lw	x6, 1664(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1664(x5)\n" // * i = a;
"lw	x6, 1668(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1668(x5)\n" // * i = a;
"lw	x6, 1672(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1672(x5)\n" // * i = a;
"lw	x6, 1676(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1676(x5)\n" // * i = a;
"lw	x6, 1680(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1680(x5)\n" // * i = a;
"lw	x6, 1684(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1684(x5)\n" // * i = a;
"lw	x6, 1688(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1688(x5)\n" // * i = a;
"lw	x6, 1692(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1692(x5)\n" // * i = a;
"lw	x6, 1696(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1696(x5)\n" // * i = a;
"lw	x6, 1700(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1700(x5)\n" // * i = a;
"lw	x6, 1704(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1704(x5)\n" // * i = a;
"lw	x6, 1708(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1708(x5)\n" // * i = a;
"lw	x6, 1712(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1712(x5)\n" // * i = a;
"lw	x6, 1716(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1716(x5)\n" // * i = a;
"lw	x6, 1720(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1720(x5)\n" // * i = a;
"lw	x6, 1724(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1724(x5)\n" // * i = a;
"lw	x6, 1728(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1728(x5)\n" // * i = a;
"lw	x6, 1732(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1732(x5)\n" // * i = a;
"lw	x6, 1736(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1736(x5)\n" // * i = a;
"lw	x6, 1740(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1740(x5)\n" // * i = a;
"lw	x6, 1744(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1744(x5)\n" // * i = a;
"lw	x6, 1748(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1748(x5)\n" // * i = a;
"lw	x6, 1752(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1752(x5)\n" // * i = a;
"lw	x6, 1756(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1756(x5)\n" // * i = a;
"lw	x6, 1760(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1760(x5)\n" // * i = a;
"lw	x6, 1764(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1764(x5)\n" // * i = a;
"lw	x6, 1768(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1768(x5)\n" // * i = a;
"lw	x6, 1772(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1772(x5)\n" // * i = a;
"lw	x6, 1776(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1776(x5)\n" // * i = a;
"lw	x6, 1780(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1780(x5)\n" // * i = a;
"lw	x6, 1784(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1784(x5)\n" // * i = a;
"lw	x6, 1788(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1788(x5)\n" // * i = a;
"lw	x6, 1792(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1792(x5)\n" // * i = a;
"lw	x6, 1796(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1796(x5)\n" // * i = a;
"lw	x6, 1800(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1800(x5)\n" // * i = a;
"lw	x6, 1804(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1804(x5)\n" // * i = a;
"lw	x6, 1808(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1808(x5)\n" // * i = a;
"lw	x6, 1812(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1812(x5)\n" // * i = a;
"lw	x6, 1816(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1816(x5)\n" // * i = a;
"lw	x6, 1820(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1820(x5)\n" // * i = a;
"lw	x6, 1824(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1824(x5)\n" // * i = a;
"lw	x6, 1828(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1828(x5)\n" // * i = a;
"lw	x6, 1832(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1832(x5)\n" // * i = a;
"lw	x6, 1836(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1836(x5)\n" // * i = a;
"lw	x6, 1840(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1840(x5)\n" // * i = a;
"lw	x6, 1844(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1844(x5)\n" // * i = a;
"lw	x6, 1848(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1848(x5)\n" // * i = a;
"lw	x6, 1852(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1852(x5)\n" // * i = a;
"lw	x6, 1856(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1856(x5)\n" // * i = a;
"lw	x6, 1860(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1860(x5)\n" // * i = a;
"lw	x6, 1864(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1864(x5)\n" // * i = a;
"lw	x6, 1868(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1868(x5)\n" // * i = a;
"lw	x6, 1872(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1872(x5)\n" // * i = a;
"lw	x6, 1876(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1876(x5)\n" // * i = a;
"lw	x6, 1880(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1880(x5)\n" // * i = a;
"lw	x6, 1884(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1884(x5)\n" // * i = a;
"lw	x6, 1888(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1888(x5)\n" // * i = a;
"lw	x6, 1892(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1892(x5)\n" // * i = a;
"lw	x6, 1896(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1896(x5)\n" // * i = a;
"lw	x6, 1900(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1900(x5)\n" // * i = a;
"lw	x6, 1904(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1904(x5)\n" // * i = a;
"lw	x6, 1908(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1908(x5)\n" // * i = a;
"lw	x6, 1912(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1912(x5)\n" // * i = a;
"lw	x6, 1916(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1916(x5)\n" // * i = a;
"lw	x6, 1920(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1920(x5)\n" // * i = a;
"lw	x6, 1924(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1924(x5)\n" // * i = a;
"lw	x6, 1928(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1928(x5)\n" // * i = a;
"lw	x6, 1932(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1932(x5)\n" // * i = a;
"lw	x6, 1936(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1936(x5)\n" // * i = a;
"lw	x6, 1940(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1940(x5)\n" // * i = a;
"lw	x6, 1944(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1944(x5)\n" // * i = a;
"lw	x6, 1948(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1948(x5)\n" // * i = a;
"lw	x6, 1952(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1952(x5)\n" // * i = a;
"lw	x6, 1956(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1956(x5)\n" // * i = a;
"lw	x6, 1960(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1960(x5)\n" // * i = a;
"lw	x6, 1964(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1964(x5)\n" // * i = a;
"lw	x6, 1968(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1968(x5)\n" // * i = a;
"lw	x6, 1972(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1972(x5)\n" // * i = a;
"lw	x6, 1976(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1976(x5)\n" // * i = a;
"lw	x6, 1980(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1980(x5)\n" // * i = a;
"lw	x6, 1984(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1984(x5)\n" // * i = a;
"lw	x6, 1988(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1988(x5)\n" // * i = a;
"lw	x6, 1992(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1992(x5)\n" // * i = a;
"lw	x6, 1996(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1996(x5)\n" // * i = a;
"lw	x6, 2000(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2000(x5)\n" // * i = a;
"lw	x6, 2004(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2004(x5)\n" // * i = a;
"lw	x6, 2008(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2008(x5)\n" // * i = a;
"lw	x6, 2012(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2012(x5)\n" // * i = a;
"lw	x6, 2016(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2016(x5)\n" // * i = a;
"lw	x6, 2020(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2020(x5)\n" // * i = a;
"lw	x6, 2024(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2024(x5)\n" // * i = a;
"lw	x6, 2028(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2028(x5)\n" // * i = a;
"lw	x6, 2032(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2032(x5)\n" // * i = a;
"lw	x6, 2036(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2036(x5)\n" // * i = a;
"lw	x6, 2040(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2040(x5)\n" // * i = a;
"lw	x6, 2044(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2044(x5)\n" // * i = a;
"lw	x6, 0(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 0(x7)\n" // * i = a;
"lw	x6, 4(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 4(x7)\n" // * i = a;
"lw	x6, 8(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 8(x7)\n" // * i = a;
"lw	x6, 12(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 12(x7)\n" // * i = a;
"lw	x6, 16(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 16(x7)\n" // * i = a;
"lw	x6, 20(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 20(x7)\n" // * i = a;
"lw	x6, 24(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 24(x7)\n" // * i = a;
"lw	x6, 28(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 28(x7)\n" // * i = a;
"lw	x6, 32(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 32(x7)\n" // * i = a;
"lw	x6, 36(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 36(x7)\n" // * i = a;
"lw	x6, 40(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 40(x7)\n" // * i = a;
"lw	x6, 44(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 44(x7)\n" // * i = a;
"lw	x6, 48(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 48(x7)\n" // * i = a;
"lw	x6, 52(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 52(x7)\n" // * i = a;
"lw	x6, 56(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 56(x7)\n" // * i = a;
"lw	x6, 60(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 60(x7)\n" // * i = a;
"lw	x6, 64(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 64(x7)\n" // * i = a;
"lw	x6, 68(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 68(x7)\n" // * i = a;
"lw	x6, 72(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 72(x7)\n" // * i = a;
"lw	x6, 76(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 76(x7)\n" // * i = a;
"lw	x6, 80(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 80(x7)\n" // * i = a;
"lw	x6, 84(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 84(x7)\n" // * i = a;
"lw	x6, 88(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 88(x7)\n" // * i = a;
"lw	x6, 92(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 92(x7)\n" // * i = a;
"lw	x6, 96(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 96(x7)\n" // * i = a;
"lw	x6, 100(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 100(x7)\n" // * i = a;
"lw	x6, 104(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 104(x7)\n" // * i = a;
"lw	x6, 108(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 108(x7)\n" // * i = a;
"lw	x6, 112(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 112(x7)\n" // * i = a;
"lw	x6, 116(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 116(x7)\n" // * i = a;
"lw	x6, 120(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 120(x7)\n" // * i = a;
"lw	x6, 124(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 124(x7)\n" // * i = a;
"lw	x6, 128(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 128(x7)\n" // * i = a;
"lw	x6, 132(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 132(x7)\n" // * i = a;
"lw	x6, 136(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 136(x7)\n" // * i = a;
"lw	x6, 140(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 140(x7)\n" // * i = a;
"lw	x6, 144(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 144(x7)\n" // * i = a;
"lw	x6, 148(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 148(x7)\n" // * i = a;
"lw	x6, 152(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 152(x7)\n" // * i = a;
"lw	x6, 156(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 156(x7)\n" // * i = a;
"lw	x6, 160(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 160(x7)\n" // * i = a;
"lw	x6, 164(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 164(x7)\n" // * i = a;
"lw	x6, 168(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 168(x7)\n" // * i = a;
"lw	x6, 172(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 172(x7)\n" // * i = a;
"lw	x6, 176(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 176(x7)\n" // * i = a;
"lw	x6, 180(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 180(x7)\n" // * i = a;
"lw	x6, 184(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 184(x7)\n" // * i = a;
"lw	x6, 188(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 188(x7)\n" // * i = a;
"lw	x6, 192(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 192(x7)\n" // * i = a;
"lw	x6, 196(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 196(x7)\n" // * i = a;
"lw	x6, 200(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 200(x7)\n" // * i = a;
"lw	x6, 204(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 204(x7)\n" // * i = a;
"lw	x6, 208(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 208(x7)\n" // * i = a;
"lw	x6, 212(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 212(x7)\n" // * i = a;
"lw	x6, 216(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 216(x7)\n" // * i = a;
"lw	x6, 220(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 220(x7)\n" // * i = a;
"lw	x6, 224(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 224(x7)\n" // * i = a;
"lw	x6, 228(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 228(x7)\n" // * i = a;
"lw	x6, 232(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 232(x7)\n" // * i = a;
"lw	x6, 236(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 236(x7)\n" // * i = a;
"lw	x6, 240(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 240(x7)\n" // * i = a;
"lw	x6, 244(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 244(x7)\n" // * i = a;
"lw	x6, 248(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 248(x7)\n" // * i = a;
"lw	x6, 252(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 252(x7)\n" // * i = a;
"lw	x6, 256(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 256(x7)\n" // * i = a;
"lw	x6, 260(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 260(x7)\n" // * i = a;
"lw	x6, 264(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 264(x7)\n" // * i = a;
"lw	x6, 268(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 268(x7)\n" // * i = a;
"lw	x6, 272(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 272(x7)\n" // * i = a;
"lw	x6, 276(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 276(x7)\n" // * i = a;
"lw	x6, 280(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 280(x7)\n" // * i = a;
"lw	x6, 284(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 284(x7)\n" // * i = a;
"lw	x6, 288(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 288(x7)\n" // * i = a;
"lw	x6, 292(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 292(x7)\n" // * i = a;
"lw	x6, 296(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 296(x7)\n" // * i = a;
"lw	x6, 300(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 300(x7)\n" // * i = a;
"lw	x6, 304(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 304(x7)\n" // * i = a;
"lw	x6, 308(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 308(x7)\n" // * i = a;
"lw	x6, 312(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 312(x7)\n" // * i = a;
"lw	x6, 316(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 316(x7)\n" // * i = a;
"lw	x6, 320(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 320(x7)\n" // * i = a;
"lw	x6, 324(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 324(x7)\n" // * i = a;
"lw	x6, 328(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 328(x7)\n" // * i = a;
"lw	x6, 332(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 332(x7)\n" // * i = a;
"lw	x6, 336(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 336(x7)\n" // * i = a;
"lw	x6, 340(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 340(x7)\n" // * i = a;
"lw	x6, 344(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 344(x7)\n" // * i = a;
"lw	x6, 348(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 348(x7)\n" // * i = a;
"lw	x6, 352(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 352(x7)\n" // * i = a;
"lw	x6, 356(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 356(x7)\n" // * i = a;
"lw	x6, 360(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 360(x7)\n" // * i = a;
"lw	x6, 364(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 364(x7)\n" // * i = a;
"lw	x6, 368(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 368(x7)\n" // * i = a;
"lw	x6, 372(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 372(x7)\n" // * i = a;
"lw	x6, 376(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 376(x7)\n" // * i = a;
"lw	x6, 380(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 380(x7)\n" // * i = a;
"lw	x6, 384(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 384(x7)\n" // * i = a;
"lw	x6, 388(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 388(x7)\n" // * i = a;
"lw	x6, 392(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 392(x7)\n" // * i = a;
"lw	x6, 396(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 396(x7)\n" // * i = a;
"lw	x6, 400(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 400(x7)\n" // * i = a;
"lw	x6, 404(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 404(x7)\n" // * i = a;
"lw	x6, 408(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 408(x7)\n" // * i = a;
"lw	x6, 412(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 412(x7)\n" // * i = a;
"lw	x6, 416(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 416(x7)\n" // * i = a;
"lw	x6, 420(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 420(x7)\n" // * i = a;
"lw	x6, 424(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 424(x7)\n" // * i = a;
"lw	x6, 428(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 428(x7)\n" // * i = a;
"lw	x6, 432(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 432(x7)\n" // * i = a;
"lw	x6, 436(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 436(x7)\n" // * i = a;
"lw	x6, 440(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 440(x7)\n" // * i = a;
"lw	x6, 444(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 444(x7)\n" // * i = a;
"lw	x6, 448(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 448(x7)\n" // * i = a;
"lw	x6, 452(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 452(x7)\n" // * i = a;
"lw	x6, 456(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 456(x7)\n" // * i = a;
"lw	x6, 460(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 460(x7)\n" // * i = a;
"lw	x6, 464(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 464(x7)\n" // * i = a;
"lw	x6, 468(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 468(x7)\n" // * i = a;
"lw	x6, 472(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 472(x7)\n" // * i = a;
"lw	x6, 476(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 476(x7)\n" // * i = a;
"lw	x6, 480(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 480(x7)\n" // * i = a;
"lw	x6, 484(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 484(x7)\n" // * i = a;
"lw	x6, 488(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 488(x7)\n" // * i = a;
"lw	x6, 492(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 492(x7)\n" // * i = a;
"lw	x6, 496(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 496(x7)\n" // * i = a;
"lw	x6, 500(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 500(x7)\n" // * i = a;
"lw	x6, 504(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 504(x7)\n" // * i = a;
"lw	x6, 508(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 508(x7)\n" // * i = a;
"lw	x6, 512(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 512(x7)\n" // * i = a;
"lw	x6, 516(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 516(x7)\n" // * i = a;
"lw	x6, 520(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 520(x7)\n" // * i = a;
"lw	x6, 524(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 524(x7)\n" // * i = a;
"lw	x6, 528(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 528(x7)\n" // * i = a;
"lw	x6, 532(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 532(x7)\n" // * i = a;
"lw	x6, 536(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 536(x7)\n" // * i = a;
"lw	x6, 540(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 540(x7)\n" // * i = a;
"lw	x6, 544(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 544(x7)\n" // * i = a;
"lw	x6, 548(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 548(x7)\n" // * i = a;
"lw	x6, 552(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 552(x7)\n" // * i = a;
"lw	x6, 556(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 556(x7)\n" // * i = a;
"lw	x6, 560(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 560(x7)\n" // * i = a;
"lw	x6, 564(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 564(x7)\n" // * i = a;
"lw	x6, 568(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 568(x7)\n" // * i = a;
"lw	x6, 572(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 572(x7)\n" // * i = a;
"lw	x6, 576(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 576(x7)\n" // * i = a;
"lw	x6, 580(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 580(x7)\n" // * i = a;
"lw	x6, 584(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 584(x7)\n" // * i = a;
"lw	x6, 588(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 588(x7)\n" // * i = a;
"lw	x6, 592(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 592(x7)\n" // * i = a;
"lw	x6, 596(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 596(x7)\n" // * i = a;
"lw	x6, 600(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 600(x7)\n" // * i = a;
"lw	x6, 604(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 604(x7)\n" // * i = a;
"lw	x6, 608(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 608(x7)\n" // * i = a;
"lw	x6, 612(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 612(x7)\n" // * i = a;
"lw	x6, 616(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 616(x7)\n" // * i = a;
"lw	x6, 620(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 620(x7)\n" // * i = a;
"lw	x6, 624(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 624(x7)\n" // * i = a;
"lw	x6, 628(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 628(x7)\n" // * i = a;
"lw	x6, 632(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 632(x7)\n" // * i = a;
"lw	x6, 636(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 636(x7)\n" // * i = a;
"lw	x6, 640(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 640(x7)\n" // * i = a;
"lw	x6, 644(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 644(x7)\n" // * i = a;
"lw	x6, 648(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 648(x7)\n" // * i = a;
"lw	x6, 652(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 652(x7)\n" // * i = a;
"lw	x6, 656(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 656(x7)\n" // * i = a;
"lw	x6, 660(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 660(x7)\n" // * i = a;
"lw	x6, 664(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 664(x7)\n" // * i = a;
"lw	x6, 668(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 668(x7)\n" // * i = a;
"lw	x6, 672(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 672(x7)\n" // * i = a;
"lw	x6, 676(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 676(x7)\n" // * i = a;
"lw	x6, 680(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 680(x7)\n" // * i = a;
"lw	x6, 684(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 684(x7)\n" // * i = a;
"lw	x6, 688(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 688(x7)\n" // * i = a;
"lw	x6, 692(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 692(x7)\n" // * i = a;
"lw	x6, 696(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 696(x7)\n" // * i = a;
"lw	x6, 700(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 700(x7)\n" // * i = a;
"lw	x6, 704(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 704(x7)\n" // * i = a;
"lw	x6, 708(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 708(x7)\n" // * i = a;
"lw	x6, 712(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 712(x7)\n" // * i = a;
"lw	x6, 716(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 716(x7)\n" // * i = a;
"lw	x6, 720(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 720(x7)\n" // * i = a;
"lw	x6, 724(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 724(x7)\n" // * i = a;
"lw	x6, 728(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 728(x7)\n" // * i = a;
"lw	x6, 732(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 732(x7)\n" // * i = a;
"lw	x6, 736(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 736(x7)\n" // * i = a;
"lw	x6, 740(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 740(x7)\n" // * i = a;
"lw	x6, 744(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 744(x7)\n" // * i = a;
"lw	x6, 748(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 748(x7)\n" // * i = a;
"lw	x6, 752(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 752(x7)\n" // * i = a;
"lw	x6, 756(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 756(x7)\n" // * i = a;
"lw	x6, 760(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 760(x7)\n" // * i = a;
"lw	x6, 764(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 764(x7)\n" // * i = a;
"lw	x6, 768(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 768(x7)\n" // * i = a;
"lw	x6, 772(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 772(x7)\n" // * i = a;
"lw	x6, 776(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 776(x7)\n" // * i = a;
"lw	x6, 780(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 780(x7)\n" // * i = a;
"lw	x6, 784(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 784(x7)\n" // * i = a;
"lw	x6, 788(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 788(x7)\n" // * i = a;
"lw	x6, 792(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 792(x7)\n" // * i = a;
"lw	x6, 796(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 796(x7)\n" // * i = a;
"lw	x6, 800(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 800(x7)\n" // * i = a;
"lw	x6, 804(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 804(x7)\n" // * i = a;
"lw	x6, 808(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 808(x7)\n" // * i = a;
"lw	x6, 812(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 812(x7)\n" // * i = a;
"lw	x6, 816(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 816(x7)\n" // * i = a;
"lw	x6, 820(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 820(x7)\n" // * i = a;
"lw	x6, 824(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 824(x7)\n" // * i = a;
"lw	x6, 828(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 828(x7)\n" // * i = a;
"lw	x6, 832(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 832(x7)\n" // * i = a;
"lw	x6, 836(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 836(x7)\n" // * i = a;
"lw	x6, 840(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 840(x7)\n" // * i = a;
"lw	x6, 844(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 844(x7)\n" // * i = a;
"lw	x6, 848(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 848(x7)\n" // * i = a;
"lw	x6, 852(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 852(x7)\n" // * i = a;
"lw	x6, 856(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 856(x7)\n" // * i = a;
"lw	x6, 860(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 860(x7)\n" // * i = a;
"lw	x6, 864(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 864(x7)\n" // * i = a;
"lw	x6, 868(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 868(x7)\n" // * i = a;
"lw	x6, 872(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 872(x7)\n" // * i = a;
"lw	x6, 876(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 876(x7)\n" // * i = a;
"lw	x6, 880(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 880(x7)\n" // * i = a;
"lw	x6, 884(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 884(x7)\n" // * i = a;
"lw	x6, 888(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 888(x7)\n" // * i = a;
"lw	x6, 892(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 892(x7)\n" // * i = a;
"lw	x6, 896(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 896(x7)\n" // * i = a;
"lw	x6, 900(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 900(x7)\n" // * i = a;
"lw	x6, 904(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 904(x7)\n" // * i = a;
"lw	x6, 908(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 908(x7)\n" // * i = a;
"lw	x6, 912(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 912(x7)\n" // * i = a;
"lw	x6, 916(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 916(x7)\n" // * i = a;
"lw	x6, 920(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 920(x7)\n" // * i = a;
"lw	x6, 924(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 924(x7)\n" // * i = a;
"lw	x6, 928(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 928(x7)\n" // * i = a;
"lw	x6, 932(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 932(x7)\n" // * i = a;
"lw	x6, 936(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 936(x7)\n" // * i = a;
"lw	x6, 940(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 940(x7)\n" // * i = a;
"lw	x6, 944(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 944(x7)\n" // * i = a;
"lw	x6, 948(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 948(x7)\n" // * i = a;
"lw	x6, 952(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 952(x7)\n" // * i = a;
"lw	x6, 956(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 956(x7)\n" // * i = a;
"lw	x6, 960(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 960(x7)\n" // * i = a;
"lw	x6, 964(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 964(x7)\n" // * i = a;
"lw	x6, 968(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 968(x7)\n" // * i = a;
"lw	x6, 972(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 972(x7)\n" // * i = a;
"lw	x6, 976(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 976(x7)\n" // * i = a;
"lw	x6, 980(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 980(x7)\n" // * i = a;
"lw	x6, 984(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 984(x7)\n" // * i = a;
"lw	x6, 988(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 988(x7)\n" // * i = a;
"lw	x6, 992(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 992(x7)\n" // * i = a;
"lw	x6, 996(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 996(x7)\n" // * i = a;
"lw	x6, 1000(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1000(x7)\n" // * i = a;
"lw	x6, 1004(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1004(x7)\n" // * i = a;
"lw	x6, 1008(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1008(x7)\n" // * i = a;
"lw	x6, 1012(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1012(x7)\n" // * i = a;
"lw	x6, 1016(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1016(x7)\n" // * i = a;
"lw	x6, 1020(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1020(x7)\n" // * i = a;
"lw	x6, 1024(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1024(x7)\n" // * i = a;
"lw	x6, 1028(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1028(x7)\n" // * i = a;
"lw	x6, 1032(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1032(x7)\n" // * i = a;
"lw	x6, 1036(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1036(x7)\n" // * i = a;
"lw	x6, 1040(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1040(x7)\n" // * i = a;
"lw	x6, 1044(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1044(x7)\n" // * i = a;
"lw	x6, 1048(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1048(x7)\n" // * i = a;
"lw	x6, 1052(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1052(x7)\n" // * i = a;
"lw	x6, 1056(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1056(x7)\n" // * i = a;
"lw	x6, 1060(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1060(x7)\n" // * i = a;
"lw	x6, 1064(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1064(x7)\n" // * i = a;
"lw	x6, 1068(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1068(x7)\n" // * i = a;
"lw	x6, 1072(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1072(x7)\n" // * i = a;
"lw	x6, 1076(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1076(x7)\n" // * i = a;
"lw	x6, 1080(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1080(x7)\n" // * i = a;
"lw	x6, 1084(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1084(x7)\n" // * i = a;
"lw	x6, 1088(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1088(x7)\n" // * i = a;
"lw	x6, 1092(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1092(x7)\n" // * i = a;
"lw	x6, 1096(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1096(x7)\n" // * i = a;
"lw	x6, 1100(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1100(x7)\n" // * i = a;
"lw	x6, 1104(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1104(x7)\n" // * i = a;
"lw	x6, 1108(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1108(x7)\n" // * i = a;
"lw	x6, 1112(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1112(x7)\n" // * i = a;
"lw	x6, 1116(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1116(x7)\n" // * i = a;
"lw	x6, 1120(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1120(x7)\n" // * i = a;
"lw	x6, 1124(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1124(x7)\n" // * i = a;
"lw	x6, 1128(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1128(x7)\n" // * i = a;
"lw	x6, 1132(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1132(x7)\n" // * i = a;
"lw	x6, 1136(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1136(x7)\n" // * i = a;
"lw	x6, 1140(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1140(x7)\n" // * i = a;
"lw	x6, 1144(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1144(x7)\n" // * i = a;
"lw	x6, 1148(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1148(x7)\n" // * i = a;
"lw	x6, 1152(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1152(x7)\n" // * i = a;
"lw	x6, 1156(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1156(x7)\n" // * i = a;
"lw	x6, 1160(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1160(x7)\n" // * i = a;
"lw	x6, 1164(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1164(x7)\n" // * i = a;
"lw	x6, 1168(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1168(x7)\n" // * i = a;
"lw	x6, 1172(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1172(x7)\n" // * i = a;
"lw	x6, 1176(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1176(x7)\n" // * i = a;
"lw	x6, 1180(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1180(x7)\n" // * i = a;
"lw	x6, 1184(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1184(x7)\n" // * i = a;
"lw	x6, 1188(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1188(x7)\n" // * i = a;
"lw	x6, 1192(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1192(x7)\n" // * i = a;
"lw	x6, 1196(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1196(x7)\n" // * i = a;
"lw	x6, 1200(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1200(x7)\n" // * i = a;
"lw	x6, 1204(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1204(x7)\n" // * i = a;
"lw	x6, 1208(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1208(x7)\n" // * i = a;
"lw	x6, 1212(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1212(x7)\n" // * i = a;
"lw	x6, 1216(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1216(x7)\n" // * i = a;
"lw	x6, 1220(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1220(x7)\n" // * i = a;
"lw	x6, 1224(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1224(x7)\n" // * i = a;
"lw	x6, 1228(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1228(x7)\n" // * i = a;
"lw	x6, 1232(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1232(x7)\n" // * i = a;
"lw	x6, 1236(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1236(x7)\n" // * i = a;
"lw	x6, 1240(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1240(x7)\n" // * i = a;
"lw	x6, 1244(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1244(x7)\n" // * i = a;
"lw	x6, 1248(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1248(x7)\n" // * i = a;
"lw	x6, 1252(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1252(x7)\n" // * i = a;
"lw	x6, 1256(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1256(x7)\n" // * i = a;
"lw	x6, 1260(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1260(x7)\n" // * i = a;
"lw	x6, 1264(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1264(x7)\n" // * i = a;
"lw	x6, 1268(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1268(x7)\n" // * i = a;
"lw	x6, 1272(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1272(x7)\n" // * i = a;
"lw	x6, 1276(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1276(x7)\n" // * i = a;
"lw	x6, 1280(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1280(x7)\n" // * i = a;
"lw	x6, 1284(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1284(x7)\n" // * i = a;
"lw	x6, 1288(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1288(x7)\n" // * i = a;
"lw	x6, 1292(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1292(x7)\n" // * i = a;
"lw	x6, 1296(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1296(x7)\n" // * i = a;
"lw	x6, 1300(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1300(x7)\n" // * i = a;
"lw	x6, 1304(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1304(x7)\n" // * i = a;
"lw	x6, 1308(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1308(x7)\n" // * i = a;
"lw	x6, 1312(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1312(x7)\n" // * i = a;
"lw	x6, 1316(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1316(x7)\n" // * i = a;
"lw	x6, 1320(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1320(x7)\n" // * i = a;
"lw	x6, 1324(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1324(x7)\n" // * i = a;
"lw	x6, 1328(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1328(x7)\n" // * i = a;
"lw	x6, 1332(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1332(x7)\n" // * i = a;
"lw	x6, 1336(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1336(x7)\n" // * i = a;
"lw	x6, 1340(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1340(x7)\n" // * i = a;
"lw	x6, 1344(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1344(x7)\n" // * i = a;
"lw	x6, 1348(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1348(x7)\n" // * i = a;
"lw	x6, 1352(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1352(x7)\n" // * i = a;
"lw	x6, 1356(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1356(x7)\n" // * i = a;
"lw	x6, 1360(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1360(x7)\n" // * i = a;
"lw	x6, 1364(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1364(x7)\n" // * i = a;
"lw	x6, 1368(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1368(x7)\n" // * i = a;
"lw	x6, 1372(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1372(x7)\n" // * i = a;
"lw	x6, 1376(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1376(x7)\n" // * i = a;
"lw	x6, 1380(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1380(x7)\n" // * i = a;
"lw	x6, 1384(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1384(x7)\n" // * i = a;
"lw	x6, 1388(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1388(x7)\n" // * i = a;
"lw	x6, 1392(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1392(x7)\n" // * i = a;
"lw	x6, 1396(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1396(x7)\n" // * i = a;
"lw	x6, 1400(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1400(x7)\n" // * i = a;
"lw	x6, 1404(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1404(x7)\n" // * i = a;
"lw	x6, 1408(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1408(x7)\n" // * i = a;
"lw	x6, 1412(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1412(x7)\n" // * i = a;
"lw	x6, 1416(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1416(x7)\n" // * i = a;
"lw	x6, 1420(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1420(x7)\n" // * i = a;
"lw	x6, 1424(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1424(x7)\n" // * i = a;
"lw	x6, 1428(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1428(x7)\n" // * i = a;
"lw	x6, 1432(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1432(x7)\n" // * i = a;
"lw	x6, 1436(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1436(x7)\n" // * i = a;
"lw	x6, 1440(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1440(x7)\n" // * i = a;
"lw	x6, 1444(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1444(x7)\n" // * i = a;
"lw	x6, 1448(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1448(x7)\n" // * i = a;
"lw	x6, 1452(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1452(x7)\n" // * i = a;
"lw	x6, 1456(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1456(x7)\n" // * i = a;
"lw	x6, 1460(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1460(x7)\n" // * i = a;
"lw	x6, 1464(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1464(x7)\n" // * i = a;
"lw	x6, 1468(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1468(x7)\n" // * i = a;
"lw	x6, 1472(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1472(x7)\n" // * i = a;
"lw	x6, 1476(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1476(x7)\n" // * i = a;
"lw	x6, 1480(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1480(x7)\n" // * i = a;
"lw	x6, 1484(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1484(x7)\n" // * i = a;
"lw	x6, 1488(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1488(x7)\n" // * i = a;
"lw	x6, 1492(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1492(x7)\n" // * i = a;
"lw	x6, 1496(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1496(x7)\n" // * i = a;
"lw	x6, 1500(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1500(x7)\n" // * i = a;
"lw	x6, 1504(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1504(x7)\n" // * i = a;
"lw	x6, 1508(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1508(x7)\n" // * i = a;
"lw	x6, 1512(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1512(x7)\n" // * i = a;
"lw	x6, 1516(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1516(x7)\n" // * i = a;
"lw	x6, 1520(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1520(x7)\n" // * i = a;
"lw	x6, 1524(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1524(x7)\n" // * i = a;
"lw	x6, 1528(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1528(x7)\n" // * i = a;
"lw	x6, 1532(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1532(x7)\n" // * i = a;
"lw	x6, 1536(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1536(x7)\n" // * i = a;
"lw	x6, 1540(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1540(x7)\n" // * i = a;
"lw	x6, 1544(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1544(x7)\n" // * i = a;
"lw	x6, 1548(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1548(x7)\n" // * i = a;
"lw	x6, 1552(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1552(x7)\n" // * i = a;
"lw	x6, 1556(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1556(x7)\n" // * i = a;
"lw	x6, 1560(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1560(x7)\n" // * i = a;
"lw	x6, 1564(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1564(x7)\n" // * i = a;
"lw	x6, 1568(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1568(x7)\n" // * i = a;
"lw	x6, 1572(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1572(x7)\n" // * i = a;
"lw	x6, 1576(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1576(x7)\n" // * i = a;
"lw	x6, 1580(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1580(x7)\n" // * i = a;
"lw	x6, 1584(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1584(x7)\n" // * i = a;
"lw	x6, 1588(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1588(x7)\n" // * i = a;
"lw	x6, 1592(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1592(x7)\n" // * i = a;
"lw	x6, 1596(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1596(x7)\n" // * i = a;
"lw	x6, 1600(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1600(x7)\n" // * i = a;
"lw	x6, 1604(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1604(x7)\n" // * i = a;
"lw	x6, 1608(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1608(x7)\n" // * i = a;
"lw	x6, 1612(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1612(x7)\n" // * i = a;
"lw	x6, 1616(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1616(x7)\n" // * i = a;
"lw	x6, 1620(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1620(x7)\n" // * i = a;
"lw	x6, 1624(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1624(x7)\n" // * i = a;
"lw	x6, 1628(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1628(x7)\n" // * i = a;
"lw	x6, 1632(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1632(x7)\n" // * i = a;
"lw	x6, 1636(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1636(x7)\n" // * i = a;
"lw	x6, 1640(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1640(x7)\n" // * i = a;
"lw	x6, 1644(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1644(x7)\n" // * i = a;
"lw	x6, 1648(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1648(x7)\n" // * i = a;
"lw	x6, 1652(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1652(x7)\n" // * i = a;
"lw	x6, 1656(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1656(x7)\n" // * i = a;
"lw	x6, 1660(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1660(x7)\n" // * i = a;
"lw	x6, 1664(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1664(x7)\n" // * i = a;
"lw	x6, 1668(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1668(x7)\n" // * i = a;
"lw	x6, 1672(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1672(x7)\n" // * i = a;
"lw	x6, 1676(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1676(x7)\n" // * i = a;
"lw	x6, 1680(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1680(x7)\n" // * i = a;
"lw	x6, 1684(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1684(x7)\n" // * i = a;
"lw	x6, 1688(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1688(x7)\n" // * i = a;
"lw	x6, 1692(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1692(x7)\n" // * i = a;
"lw	x6, 1696(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1696(x7)\n" // * i = a;
"lw	x6, 1700(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1700(x7)\n" // * i = a;
"lw	x6, 1704(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1704(x7)\n" // * i = a;
"lw	x6, 1708(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1708(x7)\n" // * i = a;
"lw	x6, 1712(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1712(x7)\n" // * i = a;
"lw	x6, 1716(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1716(x7)\n" // * i = a;
"lw	x6, 1720(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1720(x7)\n" // * i = a;
"lw	x6, 1724(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1724(x7)\n" // * i = a;
"lw	x6, 1728(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1728(x7)\n" // * i = a;
"lw	x6, 1732(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1732(x7)\n" // * i = a;
"lw	x6, 1736(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1736(x7)\n" // * i = a;
"lw	x6, 1740(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1740(x7)\n" // * i = a;
"lw	x6, 1744(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1744(x7)\n" // * i = a;
"lw	x6, 1748(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1748(x7)\n" // * i = a;
"lw	x6, 1752(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1752(x7)\n" // * i = a;
"lw	x6, 1756(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1756(x7)\n" // * i = a;
"lw	x6, 1760(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1760(x7)\n" // * i = a;
"lw	x6, 1764(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1764(x7)\n" // * i = a;
"lw	x6, 1768(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1768(x7)\n" // * i = a;
"lw	x6, 1772(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1772(x7)\n" // * i = a;
"lw	x6, 1776(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1776(x7)\n" // * i = a;
"lw	x6, 1780(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1780(x7)\n" // * i = a;
"lw	x6, 1784(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1784(x7)\n" // * i = a;
"lw	x6, 1788(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1788(x7)\n" // * i = a;
"lw	x6, 1792(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1792(x7)\n" // * i = a;
"lw	x6, 1796(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1796(x7)\n" // * i = a;
"lw	x6, 1800(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1800(x7)\n" // * i = a;
"lw	x6, 1804(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1804(x7)\n" // * i = a;
"lw	x6, 1808(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1808(x7)\n" // * i = a;
"lw	x6, 1812(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1812(x7)\n" // * i = a;
"lw	x6, 1816(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1816(x7)\n" // * i = a;
"lw	x6, 1820(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1820(x7)\n" // * i = a;
"lw	x6, 1824(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1824(x7)\n" // * i = a;
"lw	x6, 1828(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1828(x7)\n" // * i = a;
"lw	x6, 1832(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1832(x7)\n" // * i = a;
"lw	x6, 1836(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1836(x7)\n" // * i = a;
"lw	x6, 1840(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1840(x7)\n" // * i = a;
"lw	x6, 1844(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1844(x7)\n" // * i = a;
"lw	x6, 1848(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1848(x7)\n" // * i = a;
"lw	x6, 1852(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1852(x7)\n" // * i = a;
"lw	x6, 1856(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1856(x7)\n" // * i = a;
"lw	x6, 1860(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1860(x7)\n" // * i = a;
"lw	x6, 1864(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1864(x7)\n" // * i = a;
"lw	x6, 1868(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1868(x7)\n" // * i = a;
"lw	x6, 1872(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1872(x7)\n" // * i = a;
"lw	x6, 1876(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1876(x7)\n" // * i = a;
"lw	x6, 1880(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1880(x7)\n" // * i = a;
"lw	x6, 1884(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1884(x7)\n" // * i = a;
"lw	x6, 1888(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1888(x7)\n" // * i = a;
"lw	x6, 1892(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1892(x7)\n" // * i = a;
"lw	x6, 1896(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1896(x7)\n" // * i = a;
"lw	x6, 1900(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1900(x7)\n" // * i = a;
"lw	x6, 1904(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1904(x7)\n" // * i = a;
"lw	x6, 1908(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1908(x7)\n" // * i = a;
"lw	x6, 1912(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1912(x7)\n" // * i = a;
"lw	x6, 1916(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1916(x7)\n" // * i = a;
"lw	x6, 1920(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1920(x7)\n" // * i = a;
"lw	x6, 1924(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1924(x7)\n" // * i = a;
"lw	x6, 1928(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1928(x7)\n" // * i = a;
"lw	x6, 1932(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1932(x7)\n" // * i = a;
"lw	x6, 1936(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1936(x7)\n" // * i = a;
"lw	x6, 1940(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1940(x7)\n" // * i = a;
"lw	x6, 1944(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1944(x7)\n" // * i = a;
"lw	x6, 1948(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1948(x7)\n" // * i = a;
"lw	x6, 1952(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1952(x7)\n" // * i = a;
"lw	x6, 1956(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1956(x7)\n" // * i = a;
"lw	x6, 1960(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1960(x7)\n" // * i = a;
"lw	x6, 1964(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1964(x7)\n" // * i = a;
"lw	x6, 1968(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1968(x7)\n" // * i = a;
"lw	x6, 1972(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1972(x7)\n" // * i = a;
"lw	x6, 1976(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1976(x7)\n" // * i = a;
"lw	x6, 1980(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1980(x7)\n" // * i = a;
"lw	x6, 1984(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1984(x7)\n" // * i = a;
"lw	x6, 1988(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1988(x7)\n" // * i = a;
"lw	x6, 1992(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1992(x7)\n" // * i = a;
"lw	x6, 1996(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 1996(x7)\n" // * i = a;
"lw	x6, 2000(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2000(x7)\n" // * i = a;
"lw	x6, 2004(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2004(x7)\n" // * i = a;
"lw	x6, 2008(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2008(x7)\n" // * i = a;
"lw	x6, 2012(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2012(x7)\n" // * i = a;
"lw	x6, 2016(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2016(x7)\n" // * i = a;
"lw	x6, 2020(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2020(x7)\n" // * i = a;
"lw	x6, 2024(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2024(x7)\n" // * i = a;
"lw	x6, 2028(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2028(x7)\n" // * i = a;
"lw	x6, 2032(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2032(x7)\n" // * i = a;
"lw	x6, 2036(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2036(x7)\n" // * i = a;
"lw	x6, 2040(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2040(x7)\n" // * i = a;
"lw	x6, 2044(x7)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 2044(x7)\n" // * i = a;
:"=r"(i) : : "x5", "x6", "x7");
i += 4092; 
if (i > 1077247) { i = 1048572;} //Flip arround memory should not be 2047 because of +4 at beginning 
TIRA = 0x0;
}
