echo "echo hello world"
echo -e "echo hello world" | bash
echo -e "$?\n"

echo "echo \"hello world\""
echo -e "echo \"hello world\"" | bash
echo -e "$?\n"

echo "echo 'hello world'"
echo -e "echo 'hello world'" | bash
echo -e "$?\n"

echo "echo hello'world'"
echo -e "echo hello'world'" | bash
echo -e "$?\n"

echo "echo hello""world"
echo -e "echo hello""world" | bash
echo -e "$?\n"

echo "echo ''"
echo -e "echo ''" | bash
echo -e "$?\n"

echo "echo \"\$PWD\""
echo -e "echo \"\$PWD\"" | bash
echo -e "$?\n"

echo "echo '\$PWD'"
echo -e "echo '\$PWD'" | bash
echo -e "$?\n"

echo "echo \"aspas ->'\""
echo -e "echo \"aspas ->'\"" | bash
echo -e "$?\n"

echo "echo \"aspas -> ' \""
echo -e "echo \"aspas -> ' \"" | bash
echo -e "$?\n"

echo "echo 'aspas ->\"'"
echo -e "echo 'aspas ->\"'" | bash
echo -e "$?\n"

echo "echo 'aspas -> \" '"
echo -e "echo 'aspas -> \" '" | bash
echo -e "$?\n"

echo "echo \"> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<\""
echo -e "echo \"> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<\"" | bash
echo -e "$?\n"

echo "echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<'"
echo -e "echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<'" | bash
echo -e "$?\n"

echo "echo \"exit_code ->\$? user ->\$USER home -> \$HOME\""
echo -e "echo \"exit_code ->\$? user ->\$USER home -> \$HOME\"" | bash
echo -e "$?\n"

echo "echo 'exit_code ->\$? user ->\$USER home -> \$HOME'"
echo -e "echo 'exit_code ->\$? user ->\$USER home -> \$HOME'" | bash
echo -e "$?\n"

echo "echo \"$\""
echo -e "echo \"$\"" | bash
echo -e "$?\n"

echo "echo '$'"
echo -e "echo '$'" | bash
echo -e "$?\n"

echo "echo $"
echo -e "echo $" | bash
echo -e "$?\n"

echo "echo \$?"
echo -e "echo \$?" | bash
echo -e "$?\n"

echo "echo \$?HELLO"
echo -e "echo \$?HELLO" | bash
echo -e "$?\n"

echo "pwd"
echo -e "pwd" | bash
echo -e "$?\n"

echo "pwd oi"
echo -e "pwd oi" | bash
echo -e "$?\n"

echo "export hello"
echo -e "export hello" | bash
echo -e "$?\n"

echo "export HELLO=123"
echo -e "export HELLO=123" | bash
echo -e "$?\n"

echo "export A-"
echo -e "export A-" | bash
echo -e "$?\n"

echo "export HELLO=123 A"
echo -e "export HELLO=123 A" | bash
echo -e "$?\n"

echo "export HELLO=\"123 A-\""
echo -e "export HELLO=\"123 A-\"" | bash
echo -e "$?\n"

echo "export hello world"
echo -e "export hello world" | bash
echo -e "$?\n"

echo "export HELLO-=123"
echo -e "export HELLO-=123" | bash
echo -e "$?\n"

echo "export ="
echo -e "export =" | bash
echo -e "$?\n"

echo "export 123"
echo -e "export 123" | bash
echo -e "$?\n"

echo "unset"
echo -e "unset" | bash
echo -e "$?\n"

echo "unset HELLO"
echo -e "unset HELLO" | bash
echo -e "$?\n"

echo "unset HELLO1 HELLO2"
echo -e "unset HELLO1 HELLO2" | bash
echo -e "$?\n"

echo "unset HOME"
echo -e "unset HOME" | bash
echo -e "$?\n"

echo "unset PATH"
echo -e "unset PATH" | bash
echo -e "$?\n"

echo "unset SHELL"
echo -e "unset SHELL" | bash
echo -e "$?\n"

echo "cd \$PWD"
echo -e "cd \$PWD" | bash
echo -e "$?\n"

echo "cd \$PWD hi "
echo -e "cd \$PWD hi " | bash
echo -e "$?\n"

echo "cd 123123"
echo -e "cd 123123" | bash
echo -e "$?\n"

echo "exit 123"
echo -e "exit 123" | bash
echo -e "$?\n"

echo "exit 298"
echo -e "exit 298" | bash
echo -e "$?\n"

echo "exit +100"
echo -e "exit +100" | bash
echo -e "$?\n"

echo "exit \"+100\""
echo -e "exit \"+100\"" | bash
echo -e "$?\n"

echo "exit +\"100\""
echo -e "exit +\"100\"" | bash
echo -e "$?\n"

echo "exit -100"
echo -e "exit -100" | bash
echo -e "$?\n"

echo "exit \"-100\""
echo -e "exit \"-100\"" | bash
echo -e "$?\n"

echo "exit -\"100\""
echo -e "exit -\"100\"" | bash
echo -e "$?\n"

echo "exit hello"
echo -e "exit hello" | bash
echo -e "$?\n"

echo "exit 42 world"
echo -e "exit 42 world" | bash
echo -e "$?\n"

echo "exit 9223372036854775807"
echo -e "exit 9223372036854775807" | bash
echo -e "$?\n"

echo "exit 9223372036854775808"
echo -e "exit 9223372036854775808" | bash
echo -e "$?\n"

echo "exit -9223372036854775807"
echo -e "exit -9223372036854775807" | bash
echo -e "$?\n"

echo "exit -9223372036854775808"
echo -e "exit -9223372036854775808" | bash
echo -e "$?\n"

echo "exit -9223372036854775809"
echo -e "exit -9223372036854775809" | bash
echo -e "$?\n"
