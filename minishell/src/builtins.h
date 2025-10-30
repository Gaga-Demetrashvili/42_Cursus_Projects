/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/20 20:35:10 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell_types.h"

int	is_builtin(const char *cmd);
int	execute_builtin(char **argv, char ***envp);

int	builtin_echo(char **argv);
int	builtin_cd(char **argv);
int	builtin_pwd(void);
int	builtin_export(char **argv, char ***envp);
int	builtin_unset(char **argv, char ***envp);
int	builtin_env(char **envp);
int	builtin_exit(char **argv);

#endif
