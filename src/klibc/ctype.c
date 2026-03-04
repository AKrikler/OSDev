#include <klibc/ctype.h>

bool isalnum(char c)
{
	return (('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

bool isalpha(char c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

bool isblank(char c)
{
	return (c == ' ' || c == '\t');
}

bool iscntrl(char c)
{
	return (c == '\a' || c == '\n' || c == '\r' || c == '\t' || c == '\0');
}

bool isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

bool isgraph(char c)
{
	return ('!' <= c && c <= '}');
}

bool islower(char c)
{
	return ('a' <= c && c <= 'z');
}

bool isprint(char c)
{
	return isgraph(c) || (c == ' ');
}

bool ispunct(char c)
{
	return (('!' <= c && c <= '/') || (':' <= c && c <= '@' && !(c == '<' || c == '=' || c == '>')) || ('[' <= c && c <= '`') || ('{' <= c && c <= '~'));
}

bool isspace(char c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

bool isupper(char c)
{
	return ('A' <= c && c <= 'Z');
}

bool isxdigit(char c)
{
	return (('0' <= c && c <= '9') || ('A' <= c && c <= 'F'));
}

char tolower(char c)
{
	if ('A' > c || c > 'Z')
	{
		return c;
	}
	else
	{
		return c + ('a' - 'A');
	}
}

char toupper(char c)
{
	if ('A' > c || c > 'z')
	{
		return c;
	}
	else
	{
		return c - ('a' - 'A');
	}
}