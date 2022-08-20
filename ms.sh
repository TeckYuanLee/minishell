echo -e "echo hello world\necho \$?q" | ./minishell
echo -e ""

echo -e "echo \"hello world\"\necho \$?q" | ./minishell
echo -e ""

echo -e "echo 'hello world'\necho \$?q" | ./minishell
echo -e ""

echo -e "echo hello'world'\necho \$?q" | ./minishell
echo -e ""

echo -e "echo hello""world\necho \$?q" | ./minishell
echo -e ""

echo -e "echo ''\necho \$?q" | ./minishell
echo -e ""

echo -e "echo \"\$PWD\"\necho \$?q" | ./minishell
echo -e ""

echo -e "echo '\$PWD'\necho \$?q" | ./minishell
echo -e ""

echo -e "echo \"aspas ->'\"\necho \$?q" | ./minishell
echo -e ""

echo -e "echo \"aspas -> ' \"\necho \$?q" | ./minishell
echo -e ""

echo -e "echo 'aspas ->\"'\necho \$?q" | ./minishell
echo -e ""

echo -e "echo 'aspas -> \" '\necho \$?q" | ./minishell
echo -e ""

echo -e "echo \"> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<\"\necho \$?q" | ./minishell
echo -e ""

echo -e "echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<'\necho \$?q" | ./minishell
echo -e ""

echo -e "echo \"exit_code ->\$? user ->\$USER home -> \$HOME\"\necho \$?q" | ./minishell
echo -e ""

echo -e "echo 'exit_code ->\$? user ->\$USER home -> \$HOME'\necho \$?q" | ./minishell
echo -e ""

echo -e "echo \"$\"\necho \$?q" | ./minishell
echo -e ""

echo -e "echo '$'\necho \$?q" | ./minishell
echo -e ""

echo -e "echo $\necho \$?q" | ./minishell
echo -e ""

echo -e "echo \$?\necho \$?q" | ./minishell
echo -e ""

echo -e "echo \$?HELLO\necho \$?q" | ./minishell
echo -e ""

echo -e "pwd\necho \$?q" | ./minishell
echo -e ""

echo -e "pwd oi\necho \$?q" | ./minishell
echo -e ""

echo -e "export hello\necho \$?q" | ./minishell
echo -e ""

echo -e "export HELLO=123\necho \$?q" | ./minishell
echo -e ""

echo -e "export A-\necho \$?q" | ./minishell
echo -e ""

echo -e "export HELLO=123 A\necho \$?q" | ./minishell
echo -e ""

echo -e "export HELLO=\"123 A-\"\necho \$?q" | ./minishell
echo -e ""

echo -e "export hello world\necho \$?q" | ./minishell
echo -e ""

echo -e "export HELLO-=123\necho \$?q" | ./minishell
echo -e ""

echo -e "export =\necho \$?q" | ./minishell
echo -e ""

echo -e "export 123\necho \$?q" | ./minishell
echo -e ""

echo -e "unset\necho \$?q" | ./minishell
echo -e ""

echo -e "unset HELLO\necho \$?q" | ./minishell
echo -e ""

echo -e "unset HELLO1 HELLO2\necho \$?q" | ./minishell
echo -e ""

echo -e "unset HOME\necho \$?q" | ./minishell
echo -e ""

echo -e "unset PATH\necho \$?q" | ./minishell
echo -e ""

echo -e "unset SHELL\necho \$?q" | ./minishell
echo -e ""

echo -e "cd \$PWD\necho \$?q" | ./minishell
echo -e ""

echo -e "cd \$PWD hi \necho \$?q" | ./minishell
echo -e ""

echo -e "cd 123123\necho \$?q" | ./minishell
echo -e ""

echo -e "exit 123\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit 298\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit +100\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit \"+100\"\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit +\"100\"\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit -100\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit \"-100\"\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit -\"100\"\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit hello\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit 42 world\necho \$?q" | ./minishell
echo -e ""

echo -e "exit 9223372036854775807\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit 9223372036854775808\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit -9223372036854775807\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit -9223372036854775808\necho \$?q" | ./minishell
echo -e "$?q\n"

echo -e "exit -9223372036854775809\necho \$?q" | ./minishell
echo -e "$?q\n"
