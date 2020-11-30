// Banker's Algorithm
#include <stdio.h>
#include <stdbool.h>

void a(int n, int m, int alloc[n][m], int max[n][m])
{
    int i, j, k;

    int avail[4] = {1, 5, 2, 0}; // Available Resources

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    bool safefound = true;
    for (i = 0; i < n; i++)
    {
        if (f[i] != 1)
        {
            printf("Safe Sequence could not be found.\n");
            safefound = false;
            break;
        }
    }

    if (safefound)
    {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++)
            printf("P%d -> ", ans[i]);
        printf("P%d\n", ans[n - 1]);
    }

    return;
}

bool b(int n, int m, int alloc[n][m], int max[n][m], int proc[n])
{
    int i, j, k;

    int avail[4] = {1, 5, 2, 0}; // Available Resources

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    for (i = 0; i < n; i++)
        if (f[i] != 1 || ans[i] != proc[i])
        {
            return false;
        }

    return true;
}

void c(int n, int m, int alloc[n][m], int max[n][m], int alloctest[n][m])
{
    int i, j, k;

    int avail[4] = {1, 5, 2, 0}; // Available Resources

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        
    }
    return;
}

int main()
{
    // P0, P1, P2, P3, P4 are the Process names here

    int n, m, i, j, k;
    n = 5;                            // Number of processes
    m = 4;                            // Number of resources
    int alloc[5][4] = {{0, 0, 1, 2},  // P0    // Allocation Matrix
                       {1, 0, 0, 0},  // P1
                       {1, 3, 5, 4},  // P2
                       {0, 6, 3, 2},  // P3
                       {0, 0, 1, 4}}; // P4

    int max[5][4] = {{0, 0, 1, 2},  // P0    // MAX Matrix
                     {1, 7, 5, 0},  // P1
                     {2, 3, 5, 6},  // P2
                     {0, 6, 5, 2},  // P3
                     {0, 6, 5, 6}}; // P4

    for (i = 0; i < n; i++)
    {
        printf("\nEnter resources allocated by Process %d : ", i);
        for (j = 0; j < m; j++)
        {

            scanf("%d", &alloc[i][j]);
        }
    }
    for (i = 0; i < n; i++)
    {
        printf("\nEnter Maximum resources used for Process %d: ", i);
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    //a(n ,m, alloc, max);
    int proc[n];
    printf("\nEnter the order of processes: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &proc[i]);
    }
    if (b(n, m, alloc, max, proc))
    {
        printf("True");
    }
    else
    {
        printf("False");
    }
}