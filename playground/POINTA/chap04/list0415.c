int str_lengths(const char *s)
{
    int len = 0;
    for ( ; *s!= '\0'; s++)
        len++;
    return len;
}
