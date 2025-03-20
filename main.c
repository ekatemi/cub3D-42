#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include "cub_3d.h"


char	*ft_strndup(const char *s1, int n)
{
	int			i;
	char			*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (n + 1)); // Allocate memory for n characters + null-terminator
	if (copy == NULL)
		return (NULL);
	while (i < n && s1[i] != '\0') // Copy up to n characters or stop at the null-terminator
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0'; // Ensure null-termination
	return (copy);
}
//free 2D array
char	**free_matrix(char **arr_of_words, int col)
{
	int	i;

	i = 0;
	while (i < col && arr_of_words[i])
	{
		free(arr_of_words[i]);
		i++;
	}
	free(arr_of_words);
	return (NULL);
}

//helper
void printInput(t_data data)
{
    printf("NO %s \n", data.NO);
    printf("SO %s \n", data.SO);
    printf("WE %s \n", data.WE);
    printf("EA %s \n", data.EA);
    printf("EA %c \n", data.filled);
    printf("Floor %d, %d, %d \n", data.F.r,data.F.g, data.F.b);
    printf("Ceiling %d, %d, %d \n", data.C.r,data.C.g, data.C.b);
}


// find identifyer
int extractTexture(char *str, t_data *data)
{
    if (!str || !data)
        return (0);
    int i = 0;
    char **target = NULL;
    char *identifier = "";//just for print error

    while (ft_isspace(str[i])) //skip spaces at the beginning
    {
        i++;
    }

    if (ft_strncmp(&str[i], "NO", 2) == 0)
    {
       if (*target != NULL)
       {
            printf("Error: duplicated identifier %s\n", identifier);
            return (-1);
        }
       target = &data->NO;
       identifier = "NO";
    }   
    else if (ft_strncmp(&str[i], "SO", 2) == 0)
    {
        if (*target != NULL)
        {
            printf("Error: duplicated identifier %s\n", identifier);
            return (-1);
        }
        target = &data->SO;
        identifier = "SO";
    }  
    else if (ft_strncmp(&str[i], "WE", 2) == 0)
    {
        if (*target != NULL)
        {
            printf("Error: duplicated identifier %s\n", identifier);
            return (-1);
        }
        target = &data->WE;
        identifier = "WE";
    }
    else if (ft_strncmp(&str[i], "EA", 2) == 0)
    {
        if (*target != NULL)
        {
            printf("Error: duplicated identifier %s\n", identifier);
            return (-1);
        }
        target = &data->EA;
        identifier = "EA";
    }
    //no valid identifier for path found
    if (!target || ( str[i + 2] != ' ' && str[i + 2] != '\0'))
        return (0);
    i += 2;
    
    while (ft_isspace(str[i]))
        i++;

    // if (*target != NULL)//duplicated
    // {
    //     printf("Error: duplicated identifier %s\n", identifier);
    //     return (-1);
    // }
    //strndup till last not empty space char
    int len = ft_strlen(str);
    while(len > 0 && ft_isspace(str[len-1]))
    {
        len--;
    }

    *target = ft_strndup(&str[i], len);
    return (1);
}

/* PARSE F and C */
//parse string like this "255,0,4" andd assign to F or C
int fillColor(t_location *l, char *str)
{
    int i;
    char **arr;

    i = 0;
    arr = ft_split(str, ','); // Split string into 3 components
    if (!arr)
        return (0); // Allocation error

    // Count elements
    while (arr[i])
        i++;
    
    if (i != 3) {
        printf("Error:\n 3 parameters [R,G,B]\n");
        free_matrix(arr, 3);
        return (0); //err
    }

    // Convert strings to numbers
    l->r = ft_atoi(arr[0]);
    l->g = ft_atoi(arr[1]);
    l->b = ft_atoi(arr[2]);

    if (l->r == -1 || l->g == -1 || l->b == -1) {
        printf("Error: Invalid RGB value (must be 0-255 and only digits)\n");
        free_matrix(arr, 3);
        return (0); //err
    }
    free_matrix(arr, 3);
    return (1); // Ok
}

int extractColor(char *str, t_data *data)
{
    if (!str || !data)
        return (0);
    int i = 0;
    
    while (ft_isspace(str[i])) //skip spaces at the beginning
    {
        i++;
    }

    if (ft_strncmp(&str[i], "F", 1) == 0 && )
    {
        if (data->F.r != -1)
        {
            printf("Error: duplicated identifier F\n");
            return (-1);
        }
        fillColor(&data->F, str[i]);
    }   
    else if (ft_strncmp(&str[i], "C", 1) == 0)
    {
        if (data->C.r != -1)
        {
            printf("Error: duplicated identifier C\n");
            return (-1);
        }
        fillColor(&data->C, str[i]);
    }
    else
   
    //no valid identifier found
    if (!loc_target || ( str[i + 1] != ' ' && str[i + 1] != '\0'))
        return (0);
    i += 1;
    
    while (ft_isspace(str[i]))
        i++;

    if (loc_target != NULL)//duplicated
    {
        printf("Error: duplicated identifier %s\n", identifier);
        return (-1);
    }

    loc_target = ft_strdup(&str[i]);

    return (1);
}

//which id do we have
int checkID(char *str, t_data *data)
{
    if (!str)
        return(0);

    while(*str == ' ')
        str++;
    if ((str, "NO", 2))
        return 1;
    else if (!ft_strncmp(str, "SO", 2))
        return 2;
    else if (!ft_strncmp(str, "WE", 2))
        return 3;
    else if (!ft_strncmp(str, "EA", 2))
        return 4;
    else if (*str == 'F')
        return 5;
    else if (*str == 'C')
        return 6;
    return (0);
}


int parseInput(char *str)
{
   
    int i = 0;
    
    int start = 0; //
    int end = 0;

    char *identifyer = NULL;

    if (!str || ft_strlen(str) < 2)
        return (0); //err
    
    // while(ft_isspace(str[i]))
    //     i++;
    
    
    if (!arr)
        return (0); //err allocation
    

    
    
    
}



int main(int argc, char **argv)
{
    t_data data;

    inputDataInit(&data);
    printInput(data); //just to check

    char *file = getFilename(argc, argv);
    if (!file)
        return (1);
        
    int     fd;
    char    *result;
    //char    **matrix;
    
    fd = errOpen(file);
    if (fd == -1)
    {
       return (1); 
    }
    
    result = get_next_line(fd); //if result is empty line skip to next
    //printf("Result is %s\n", result);
    while (result)	
    {
        // if (is_empty_or_whitespace(result))
        // {
        //     free(result);
        //     result = get_next_line(fd);  // Continue to the next line
        //     continue;
        // }
        printf("RESULT--->>>%s", result);
        /*if not empty:
            define first chars (NO SO WE EA F C)
            skip spaces
            also check duplicated coordinates(if (!struct.NO) NO = "path" else err dupl)
            check the structure: path to file / r,g,b from 0 to 255
            fill structs
            if line is only 111111 it is start of the map
            /flag inside map = 1
            if flag inside map and empty line == error
            if line is 111111 and next lines are empty or eof is end of map
        */
        free(result);
        result = get_next_line(fd);
    }
    free(result);
    close(fd);
    return (0);
}