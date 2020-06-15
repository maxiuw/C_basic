#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main(void)
{
    int a = 5;
    int b[3];
    b[0] = true;
    b[1] = true;
    b[2] = false;

    printf("%d",b[0]);
}
// typedef struct
// {
//     int winner;
//     int loser;
// }
// pair;
// pair pairs[6];
// bool vote(int rank, string name, int ranks[]);

// int candidate_count = 3;
// string candidates[3];

// int main (int argc, string argv[])
// {
//     for (int i = 0; i < candidate_count; i++)
//     {
//         candidates[i] = argv[i + 1];
//     }

//     int ranks [candidate_count];

//     for (int j = 0; j < candidate_count; j++)

//         {
//             string name = get_string("Rank %i: ", j + 1);

//             if (!vote(j, name, ranks))
//             {
//                 printf("Invalid vote.\n");
//                 return 3;
//             }
//             printf("%i,%i,%i",ranks[0],ranks[1],ranks[2]);
//         }
//         printf("%i", strlen(pairs.winner))
// }




// bool vote(int rank, string name, int ranks[])
// {
//     for (int i = 0; i <candidate_count; i++ )
//     {
//         if (strcmp(name,candidates[i])==0)
//             {
//                 ranks[i] = rank;
//                 return true;
//             }

//     }
//     return false;
// }