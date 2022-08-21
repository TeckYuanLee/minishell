echo -e "echo\necho \$?" | ./minishell
echo -e ""

echo -e "echo echo\necho \$?" | ./minishell
echo -e ""

echo -e "eCho \necho \$?" | ./minishell
echo -e ""

echo -e "eChO\necho \$?" | ./minishell
echo -e ""

echo -e "eCHO\necho \$?" | ./minishell
echo -e ""

echo -e "ECHO\necho \$?" | ./minishell
echo -e ""

echo -e "echo rhobebou\necho \$?" | ./minishell
echo -e ""

echo -e "echo stop barking\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"bonjour\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo 'bonjour'\necho \$?" | ./minishell
echo -e ""

echo -e "echo -n bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo -nn bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo -n -n -n bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo -n -n -n bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"-n\" bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo -n\"-n\" bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"-nnnn\" bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"-n -n -n\"-n bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"-n '-n'\" bonjour\necho \$?" | ./minishell
echo -e ""

echo -e "echo ~\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"~\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo '~'\necho \$?" | ./minishell
echo -e ""

echo -e "echo ~123\necho \$?" | ./minishell
echo -e ""

echo -e "echo 123~\necho \$?" | ./minishell
echo -e ""

echo -e "echo ~/123\necho \$?" | ./minishell
echo -e ""

echo -e "echo ~/123/456\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"\$USER\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"'\$USER'\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \" '\$USER' \"\necho \$?" | ./minishell
echo -e ""

echo -e "echo text\"\$USER\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo text\"'\$USER'\" ' \$USER '\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"text\"   \"\$USER\"    \"\$USER\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo '              \$USER          '\necho \$?" | ./minishell
echo -e ""

echo -e "echo               text \"\$USER\"            \"\$USER\"text\necho \$?" | ./minishell
echo -e ""

echo -e "echo ''''''''''\$USER''''''''''\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"\"\"\"\"\"\"\"\$USER\"\"\"\"\"\"\"\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER'\$USER'text oui oui     oui  oui \$USER oui      \$USER ''\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER '' \$USER \$USER '' \$USER '' \$USER -n \$USER\necho \$?" | ./minishell
echo -e ""

echo -e "echo ' \\' ' \\'\necho \$?" | ./minishell
echo -e ""

echo -e "echo '\\\" ' \" \\\"\\\"\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \\\\\\\" \\\\\\\" \\\\\\\" \\\\\\\"\\\\\\\"\\\\\\\" \\\\\\'\\\\\\'\\\\\\'\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"\$USER\"\"\$USER\"\"\$USER\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo text\"\$USER\"test\necho \$?" | ./minishell
echo -e ""

echo -e "echo '\$USER' \"\$USER\" \"text \' text\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo '\$USER'\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER \" \"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"\$USER\"\"Users/\$USER/file\"\"'\$USER'\"'\$USER'\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"\$USER\$USER\$USER\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo '\$USER'\"\$USER\"'\$USER'\necho \$?" | ./minishell
echo -e ""

echo -e "echo '\"\$USER\"''\$USER'\"\"\"\$USER\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \" \$USER  \"'\$PWD'\necho \$?" | ./minishell
echo -e ""

echo -e "echo \" \$USER  \$ \"'\$PWD'\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER=4\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER=thallard\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$?\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER213\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER\$12USER\$USER=4\$USER12\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER \$123456789USER \$USER123456789\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER \$9999USER \$8888USER \$7777USER\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER \$USER9999 \$USER8888 \$USER7777\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$USER \$USER9999 \$USER8888 \$USER7777 \"\$USER\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"\$USER=12\$USER\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"\$9USER\" \"'\$USER=12\$SOMETHING'\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$PWD/file\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"\$PWD/file\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \"text\" \"text\$USER\" ... \"\$USER\"\necho \$?" | ./minishell
echo -e ""

echo -e "echo \$PWD\necho \$?" | ./minishell
echo -e ""

echo -e "echo test tout\necho \$?" | ./minishell
echo -e ""

echo -e "echo test      tout\necho \$?" | ./minishell
echo -e ""

echo -e "echo -n test tout\necho \$?" | ./minishell
echo -e ""

echo -e "echo -n -n -n test tout\necho \$?" | ./minishell
echo -e ""