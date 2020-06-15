#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// counting pairs and indexes of pairs sorted
// from the biggest differences between pairs to the smallest

// int pairs_count = 0;
int sorted[MAX*(MAX - 1) / 2];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pairs_count=0;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // pairs_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}


// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i <candidate_count; i++ )
    {
        if (strcmp(name,candidates[i])==0)
            {
                ranks[rank] = i;
                return true;
            }

    }
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i<candidate_count;i++)
    {
        for (int j = 0; j<candidate_count; j++)
        {
            if (i<j)
            {
                preferences[ranks[i]][ranks[j]]++;
                printf("pref %s to %s is %i\n",candidates[ranks[i]],candidates[ranks[j]],preferences[ranks[i]][ranks[j]]);
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)


{
    for (int i = 0; i<candidate_count;i++)
    {
        for (int j = 0; j<candidate_count; j++)
        {
            if (preferences[i][j]>preferences[j][i])
            {
                pairs[pairs_count].winner=i;
                pairs[pairs_count].loser=j;
                pairs_count++;
                printf("dodaje pare winner: %s i loser: %s o przewadze %i\n",candidates[i],candidates[j],preferences[i][j]);
            }


        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    int strength[pairs_count];
    for (int x = 0; x<pairs_count; x++)
    {
        strength[x]=preferences[pairs[x].winner][pairs[x].loser]-preferences[pairs[x].loser][pairs[x].winner];
        printf("dla pary %i winner %s and loser %s o przewadze %i\n",x,candidates[pairs[x].winner],candidates[pairs[x].loser],strength[x]);
    }

    for (int i = 0, l = 0; i < pairs_count; i++,l++)
    {

        int k = 0;
        do
        {
            if (strength[i]>=strength[k] || i==k)
            {
                k++;
            }
            else if (strength[i]<strength[k])
            {
                i=k;
                k++;
            }
        }
        while(k<pairs_count);
        printf("para %i o przewadze %i\n",l,strength[i]);

        strength[i] = 0;
        printf("[%i,%i,%i]",strength[0],strength[1],strength[2]);
        sorted[l] = i;
        i=l;


    }
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for (int i = 0; i<pairs_count; i++)
    {
        int counter = 0;
        if (i == 0)
        {
            locked[pairs[sorted[i]].winner][pairs[sorted[i]].loser] = true;
            for (int l =0; l < candidate_count; l++)
            {
                for (int j = 0; j <candidate_count; j++)
                {
                    printf("%d",locked[l][j]);
                }
                printf("\n");
            }

        }
        else
        {
            for(int j = 0; j < i; j++)
            {
                // is the i'th looser winner, of any winners of i'th winer,

                // check if the column pairs[sorted[i]].winner jest pusta
                // printf("locked[j][pairs[sorted[i]].winner] - [%i,%i] \n",j,pairs[sorted[i]].winner,pairs[i].loser,j)
                if (locked[j][pairs[sorted[i]].winner]==1) // why && not resutl
                {
                    if (locked[pairs[sorted[i]].loser][j]==1)
                    {
                        counter++;
                    }

                }
                // if true, check if looser[i],j ==true
            }
            if (counter == 0)
            {
                locked[pairs[sorted[i]].winner][pairs[sorted[i]].loser] = true;
                for (int n = 0; n < candidate_count; n++)
                {
                    for (int m = 0; m <candidate_count; m++)
                    {
                        printf("%d",locked[n][m]);
                    }
                    printf("\n");
                }
            }
        }
    }



}

// Print the winner of the election
void print_winner(void)
{

    //  printf("%s\n",candidates[pairs[sorted[0]].winner]);
    // int score = 0;
    // int score;
    for (int i = 0; i<pairs_count; i++)
    {
        int score = 0;

        for (int j = 0; j <pairs_count; j++)
        {
            if (locked[j][i] == 1) //1-t,0 -f
            {
                score++;
            }
        }

        if (score == 0)
            {
                printf("the winner: %s",candidates[i]);
            }
    }

    return;
}

