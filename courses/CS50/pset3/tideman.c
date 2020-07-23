#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

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

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int n, int m);

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
        //printf("candidate %i = %s\n", i, candidates[i]);
    }


    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
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

        //printf("Alice - %i, Bob - %i, Charlie - %i ", ranks[0], ranks[1], ranks[2]);

        record_preferences(ranks);

        printf("\n");
    }

    //for (int i = 0; i < candidate_count; i++)
    //{
    //    for (int j = 0; j < candidate_count; j++)
    //    {
    //        //printf("Candidate %s over candidate %s = %i\n", candidates[i], candidates[j], preferences[i][j]);
    //        printf("%s candidates[%i] over %s candidates[%i] = %i\n", candidates[i], i, candidates[j], j, preferences[i][j]);
    //    }
    //}

    add_pairs();

    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("pair %i: winner - %i, loser %i\n", i, pairs[i].winner, pairs[i].loser);
    //}


    sort_pairs();

    //printf("sorted pairs\n");

    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("pair %i: winner - %i, loser %i\n", i, pairs[i].winner, pairs[i].loser);
    //}


    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            //ranks[i] = rank;
            ranks[rank] = i;
            return true;
        }

    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // int preferences[MAX][MAX];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 1; j < candidate_count - i; j++)
            preferences[ranks[i]][ranks[i + j]]++;
            //if (ranks[i] < ranks[j])
            //{
            //    preferences[i][j] += 1;
            //}

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }

    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("Pair #%i: winner %i, loser %i\n", i, pairs[i].winner, pairs[i].loser);
    //}
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp_pair[1];

    // selection sort
    int min_idx;
    for (int i = 0; i < pair_count; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < pair_count + 1; j++)
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[min_idx].winner][pairs[min_idx].loser])
                min_idx = j;

        temp_pair[0].winner = pairs[min_idx].winner;
        temp_pair[0].loser = pairs[min_idx].loser;

        pairs[min_idx].winner = pairs[i].winner;
        pairs[min_idx].loser = pairs[i].loser;

        pairs[i].winner = temp_pair[0].winner;
        pairs[i].loser = temp_pair[0].loser;
    }
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    ////set first locked pair
    //if(pair_count > 0)
    //    locked[pairs[0].winner][pairs[0].loser] = true;
    //
    //for (int i = 1; i < pair_count; i++)
    //{
    //    bool cycle = false;
    //    for (int j = 0; j < pair_count; j++){
    //        if(locked[pairs[i].loser][j])
    //        {
    //            cycle = true;
    //            break;
    //        }
    //    }
    //
    //    //check if adding this node will create a cycle
    //    if(!cycle)
    //        locked[pairs[i].winner][pairs[i].loser] = true;
    //}
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                source = false;
                break;
            }
        }

        if (source == true)
        {
            printf("%s\n", candidates[i]);
        }
    }

    // TODO
    return;
}

//bool loopcheck(int a, int b)
//{
//    if (locked[b][a] == true)
//        return true;
//
//    for (int i = 0; i < candidate_count; i++)
//        if (locked[i][a] == true)
//            return loopcheck(i, b);
//    return false;
//}
bool check_cycle(int n, int m)
{
    if (locked[m][n] == true)
        return true;

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][n] == true)
        {
            if (check_cycle(i, m))
                return true;
            else
                return false;
        }
    }
    return false;
}