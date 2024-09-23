/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:48:48 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/23 13:05:08 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"
#include "./structs.h"

t_cmd *create_node(char *infile, char *outfile, t_token_type intype, t_token_type outype, int ispipe) {
    t_cmd *new_node = malloc(sizeof(t_cmd));
    if (!new_node) {
        perror("Failed to allocate memory");
        return NULL;
    }
    new_node->cmd = NULL; // 可以根据需要初始化
    new_node->infile = infile;
    new_node->outfile = outfile;
    new_node->intype = intype;
    new_node->outype = outype;
    new_node->ispipe = ispipe;
    new_node->next = NULL;
    return new_node;
}
void	test()
{
	  t_cmd *head = create_node("infile", NULL, TK_IN_RE, TK_NONE, 1);
    // 创建第二个节点
    t_cmd *second = create_node(NULL, "outfile", TK_NONE, TK_OUT_RE, 0);

    // 连接节点
    if (head && second) {
        head->next = second;
		head->cmd[0]="cat";
		head->next->cmd[0]="grep";
		head->next->cmd[1]="txt";
    }

	exe(head);
}
void	exe(t_cmd *cm)
{
	int i;
	i=0;
	while(cm->cmd[i])
		ft_printf("%s\n",cm->cmd[i++]);
	i=0;
	while(cm->cmd[i])
		ft_printf("%s ",cm->next->cmd[i++]);

}
