int cmpN(struct employee a, struct employee b)
{
    return strcmp(a.surname, b.surname);
}

int cmpD(struct employee a, struct employee b)
{
    return strcmp(a.dept, b.dept);
}

template<class T>
void TemplateSortRecords(T emp[50], int count, compare cmp)
{
    for (int j = 1; j < count; j++)
    {
        int i = j - 1;
        T temp = emp[j];

        while(1)
        {
            if((*cmp)(temp, emp[i]) >= 0)
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