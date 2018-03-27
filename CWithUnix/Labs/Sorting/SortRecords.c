void SortRecords(struct employee emp[50], int count)
{
    for (int j = 1; j < count; j++)
    {
        int i = j - 1;
        struct employee temp = emp[j];

        while(1)
        {
            if(strcmp(temp.dept, emp[i].dept) >= 0)
            {
                emp[i+1] = temp;
                break;
            }
            else
            {
                emp[i+1] = emp[i];
                i--;
                if (i < 0)
                {
                    emp[0] = temp;
                    break;
                }
            }

        }
    }
    return;
}