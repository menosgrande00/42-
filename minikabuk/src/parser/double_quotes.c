#include "minishell.h"

void remove_quotes_from_input(t_minishell *minishell, int j_pos, int i_pos)
{
	char *new_input;
	int len = ft_strlen(minishell->input);
	int new_len = len - 2; // İki tırnak kaldırılacak
	int k = 0;
	
	new_input = malloc(new_len + 1);
	if (!new_input)
		return;
	// j pozisyonuna kadar kopyala (açılış tırnağı hariç)
	for (int idx = 0; idx < j_pos; idx++)
		new_input[k++] = minishell->input[idx];
	
	// j+1'den i'ye kadar kopyala (tırnak içindeki içerik)
	for (int idx = j_pos + 1; idx < i_pos; idx++)
		new_input[k++] = minishell->input[idx];
	
	// i+1'den sonrasını kopyala (kapanış tırnağı hariç)
	for (int idx = i_pos + 1; idx < len; idx++)
		new_input[k++] = minishell->input[idx];
	
	new_input[k] = '\0';
	
	// Eski input'u serbest bırak ve yenisini ata
	free(minishell->input);
	minishell->input = new_input;
}

int	handle_after_quote_text(t_minishell *minishell, int *i, int j)
{
	int		current_pos;
	char	*result_text;
	char	*temp_text;
	t_token_list	*last;
	char	*combined;
	int		quote_start, quote_end;

	current_pos = *i + 1;
	result_text = ft_strdup(""); // Boş string ile başla
	if (!result_text)
		return (1);
	
	// Tırnak sonrası tüm ardışık içeriği topla
	while (minishell->input[current_pos] && minishell->input[current_pos] != ' ')
	{
		if (minishell->input[current_pos] == '"')
		{
			// Çift tırnak bulundu, içeriğini al
			quote_start = current_pos;
			quote_end = current_pos + 1;
			
			// Kapanış tırnağını bul
			while (minishell->input[quote_end] && minishell->input[quote_end] != '"')
				quote_end++;
			
			if (minishell->input[quote_end] == '"')
			{
				// Tırnak içindeki içeriği al
				char *quoted_content = ft_substr(minishell->input, quote_start + 1, 
												quote_end - quote_start - 1);
				if (quoted_content)
				{
					temp_text = ft_strjoin(result_text, quoted_content);
					free(result_text);
					free(quoted_content);
					result_text = temp_text;
					if (!result_text)
						return (1);
				}
				current_pos = quote_end + 1;
			}
			else
			{
				// Kapanmamış tırnak, hata
				free(result_text);
				return (1);
			}
		}
		else
		{
			// Normal karakter, direkt ekle
			char single_char[2] = {minishell->input[current_pos], '\0'};
			temp_text = ft_strjoin(result_text, single_char);
			free(result_text);
			result_text = temp_text;
			if (!result_text)
				return (1);
			current_pos++;
		}
	}
	
	// Son tokenı bul ve birleştir
	last = minishell->token_list;
	while (last && last->next)
		last = last->next;
	
	if (last)
	{
		combined = ft_strjoin(last->token->value, result_text);
		if (combined)
		{
			free(last->token->value);
			last->token->value = combined;
		}
	}
	free(result_text);
	
	// Tüm işlenen kısmı input'tan kaldır (tek seferde)
	char *new_input;
	int prefix_len = j;
	int remaining_start = current_pos;
	int remaining_len = ft_strlen(&minishell->input[remaining_start]);
	int new_len = prefix_len + remaining_len;
	
	new_input = malloc(new_len + 1);
	if (!new_input)
		return (1);
	
	// Prefix kısmını kopyala
	for (int idx = 0; idx < prefix_len; idx++)
		new_input[idx] = minishell->input[idx];
	
	// Kalan kısmını kopyala
	for (int idx = 0; idx < remaining_len; idx++)
		new_input[prefix_len + idx] = minishell->input[remaining_start + idx];
	
	new_input[new_len] = '\0';
	
	free(minishell->input);
	minishell->input = new_input;
	
	// Pozisyonu ayarla
	*i = j + ft_strlen(last->token->value) - 1;
	
	return (0);
}

int	merge_with_previous_token(t_minishell *minishell, t_token **current_token)
{
	t_token_list	*last;
	char			*new_value;

	last = minishell->token_list;
	while (last && last->next)
		last = last->next;
	if (last)
	{
		new_value = ft_strjoin(last->token->value, (*current_token)->value);
		if (new_value)
		{
			free(last->token->value);
			last->token->value = new_value;
		}
		free((*current_token)->value);
		free(*current_token);
	}
	else
		add_token_to_list(&minishell->token_list, *current_token);
	return (0);
}

static int	handle_quote_merging(t_minishell *minishell, int *i, t_token **current_token, int j)
{
	if (j > 0 && (minishell->input[j - 1] == '<' || minishell->input[j - 1] == '>'
		|| minishell->input[j - 1] == '|') && minishell->input[*i + 1] != '"')
	{
		add_token_to_list(&minishell->token_list, *current_token);
		remove_quotes_from_input(minishell, j, *i);
		*i = j + ft_strlen((*current_token)->value);
		return (0);
	}	
	if (minishell->input[j - 1] == ' ' && (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\0'))
	{
		add_token_to_list(&minishell->token_list, *current_token);
		(*i)++;
		return (0);
	}
	if (minishell->input[j - 1] != ' ')
	{
		merge_with_previous_token(minishell, current_token);
		if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
		{
			handle_after_quote_text(minishell, i, j);
			while (minishell->input[*i] != ' ' && minishell->input[*i] != '\0')
				(*i)++;
		}
	}
	else if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
	{
		remove_quotes_from_input(minishell, j, *i);
		*i = j - 2;
	}
	(*i)++;
	return (0);
}

static int	create_quote_token(t_minishell *minishell, int start, int i, t_token **current_token)
{
	char	*tmp;

	tmp = ft_substr(minishell->input, start, i - start);
	if (!tmp)
		return (1);
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
	{
		free(tmp);
		return (1);
	}
	(*current_token)->value = tmp;
	(*current_token)->type = TOKEN_WORD;
	(*current_token)->quotes = 1;
	return (0);
}

/////////////////////////////////////////////////

int re_build_input(t_minishell *minishell, int *i, char *value, int key_len)
{
    char *last;
    char *new_input;
    int remaining_len;
    int value_len;
    int prefix_len;
    int new_total_len;

    // Uzunlukları hesapla
    prefix_len = (*i);
    value_len = strlen(value);
    remaining_len = strlen(&minishell->input[(*i) + key_len + 1]);
    new_total_len = prefix_len + value_len + remaining_len;

    // Kalan kısmı kaydet
    last = malloc(remaining_len + 1);
    if (!last)
        return (1);
    strcpy(last, &minishell->input[(*i) + key_len + 1]);

    // Yeni input için memory ayır
    new_input = malloc(new_total_len + 1);
    if (!new_input)
    {
        free(last);
        return (1);
    }

    // Yeni string'i oluştur
    strncpy(new_input, minishell->input, prefix_len);           // Önceki kısım
    strcpy(new_input + prefix_len, value);                      // Yeni değer
    strcpy(new_input + prefix_len + value_len, last);           // Kalan kısım
    new_input[new_total_len] = '\0';

    // Eski input'u serbest bırak ve yenisini ata
    free(minishell->input);
    minishell->input = new_input;

    // Memory'yi temizle
    free(last);
    
    (*i) += value_len - 1;
    return (0);
}

char	*extract_env_key_double(t_minishell *minishell, int *i)
{
	char	*key;
	int		j;
	int		k;
	
	j = *i + 1;
	k = 0;
	while (minishell->input[j] && minishell->input[j] != ' '
		&& minishell->input[j] != '"')
	{
		j++;
		k++;
	}
	key = malloc(sizeof(char) * k + 1);
	j = *i + 1;
	k = 0;
	while(minishell->input[j] && minishell->input[j] != ' '
		&& minishell->input[j] != '"')
	{
		key[k] = minishell->input[j];
		j++;
		k++;
	}
	key[k] = '\0';
	return (key);
}


int	set_input_path(t_minishell *minishell, int *i, int *start)
{
	char	*key;
	char	*value;
	int		a = *start;

	(void)a;
	key = extract_env_key_double(minishell, i);
	if (!key)
		return (1);
	value = get_env_value(minishell->envp, key);
	if (!value)
		return (1);
	re_build_input(minishell, i, value, ft_strlen(key));
	return (0);
}

int	replace_input(t_minishell *minishell, int *i)
{
	char	*status;
	char	*last;
	int		len;
	int		j;
	int		k;

	status = ft_itoa(minishell->exit_status);
	len = *i;
	while(minishell->input[len])
		len++;
	last = malloc(len - 2);
	if (!last)
		return (1);
	j = 0;
	len = (*i) + 2;
	while (minishell->input[len])
	{
		last[j] = minishell->input[len];
		len++;
		j++;
	}
	last[j] = '\0';
	k = 0;
	len = *i;
	while (status[k])
	{
		minishell->input[len] = status[k];
		len++;
		k++;
	}
	j = 0;
	while (last[j])
	{
		minishell->input[len] = last[j];
		len++;
		j++;
	}
	minishell->input[len] = '\0';
	(*i) += k;
	return (0);
}

int	handle_dollar_in_quotes(t_minishell *minishell, int *i, int *start)
{
	int a = *start;

	(void)a;
	if (minishell->input[*i] == '$' && minishell->input[*i + 1] == '"')
	{
		(*i)++;
		return (1);
	}
	else if (minishell->input[*i] == '$' && minishell->input[*i + 1] == '?')
		replace_input(minishell, i);
	else if (minishell->input[*i] == '$')
	{
		set_input_path(minishell, i, start);
	}
	return (0);
}

int	process_quote_content(t_minishell *minishell, int *i, int *start)
{
	int	ret;

	while (minishell->input[*i] && minishell->input[*i] != '"')
	{
		if (minishell->input[*i] == '$' && minishell->input[*i + 1] 
			&& minishell->input[*i + 1] != ' ')
		{
			ret = handle_dollar_in_quotes(minishell, i, start);
			if (ret != 0)
			{
				if (ret == -1)
				    return 1;
				else
				    return 0;
			}
		}
		(*i)++;
	}
	if (minishell->input[*i] != '"')
	{
		write(2, "syntax error: unclosed quote\n", 29);
		minishell->exit_status = 2;
		return (1);
	}
	return (0);
}

int	double_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	int	start;
	int	j;
	int	ret;

	j = (*i);
	start = ++(*i);
	ret = process_quote_content(minishell, i, &start);
	if (ret != 0)
		return (ret);
	if (create_quote_token(minishell, start, *i, current_token))
		return (1);
	return (handle_quote_merging(minishell, i, current_token, j));
}
