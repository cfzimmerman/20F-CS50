#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if ((vote(name)) == false)
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int x = 0;
    int maxcandidatecount = 0;
    int candidatecounter = 0;

    for (x = 0; x < candidate_count; x++)
    {
        if (strcmp(candidates[x].name, name) == 0)
        {
            candidates[x].votes++;
            candidatecounter++;
        }
    }
    
    if (candidatecounter == 0)
    {
        return false;
    }

    return true;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int y = 0;
    int winningcount = candidates[y].votes;

    for (y = 0; y < candidate_count; y++)
    {
        if (candidates[y].votes < candidates[y + 1].votes)
        {
            winningcount = candidates[y + 1].votes;
        }
    }

    for (y = 0; y < candidate_count; y++)
    {
        if (candidates[y].votes == winningcount)
        {
            printf("%s\n", candidates[y].name);
        }
    }
    return;
}

