#!/bin/bash
echo "=== Manual Testing ==="
echo ""
echo "Test 1: Basic echo"
echo -e "echo hello world\nexit" | ./minishell 2>&1 | grep "hello world" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 2: Echo -n"
echo -e "echo -n test\nexit" | ./minishell 2>&1 | grep -E "testminishell" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 3: PWD"
echo -e "pwd\nexit" | ./minishell 2>&1 | grep "42_Cursus_Projects/minishell" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 4: CD"
echo -e "cd /tmp\npwd\nexit" | ./minishell 2>&1 | grep "/tmp" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 5: Export and Echo"
echo -e "export TEST=value\necho \$TEST\nexit" | ./minishell 2>&1 | grep "value" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 6: Env"
echo -e "export MYVAR=test123\nenv\nexit" | ./minishell 2>&1 | grep "MYVAR=test123" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 7: Unset"
echo -e "export TOUNSET=x\nunset TOUNSET\nenv\nexit" | ./minishell 2>&1 | grep "TOUNSET" && echo "❌ FAIL (should be gone)" || echo "✅ PASS"
echo ""

echo "Test 8: Exit status"
echo -e "echo test\necho \$?\nexit" | ./minishell 2>&1 | grep "^0$" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 9: Simple pipe"
echo -e "echo hello | cat\nexit" | ./minishell 2>&1 | grep "hello" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 10: Pipe with ls"
echo -e "ls | head -1\nexit" | ./minishell 2>&1 | grep -E "(Makefile|src)" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 11: Heredoc"
echo -e "cat << EOF\nline1\nline2\nEOF\nexit" | ./minishell 2>&1 | grep "line1" | grep -q "line2" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 12: Single quotes"
echo -e "echo 'hello world'\nexit" | ./minishell 2>&1 | grep "hello world" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 13: Double quotes"
echo -e 'echo "hello world"\nexit' | ./minishell 2>&1 | grep "hello world" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 14: Variable expansion in double quotes"
echo -e 'export V=expanded\necho "$V"\nexit' | ./minishell 2>&1 | grep "expanded" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 15: No expansion in single quotes"
echo -e "export V=test\necho '\$V'\nexit" | ./minishell 2>&1 | grep '\$V' && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 16: External command (/bin/echo)"
echo -e "/bin/echo test\nexit" | ./minishell 2>&1 | grep "test" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 17: AND operator"
echo -e "echo first && echo second\nexit" | ./minishell 2>&1 | grep "second" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 18: OR operator"
echo -e "nonexistent_cmd || echo fallback\nexit" | ./minishell 2>&1 | grep "fallback" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 19: Multiple exports"
echo -e "export A=1\nexport B=2\necho \$A \$B\nexit" | ./minishell 2>&1 | grep "1 2" && echo "✅ PASS" || echo "❌ FAIL"
echo ""

echo "Test 20: Complex pipe"
echo -e "echo one two | cat | cat\nexit" | ./minishell 2>&1 | grep "one two" && echo "✅ PASS" || echo "❌ FAIL"
echo ""
