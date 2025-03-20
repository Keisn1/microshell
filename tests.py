import subprocess

p = subprocess.Popen(["./microshell", "non-executable"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
        )
stdout, stderr = p.communicate();

assert stdout.decode() == "", f"wrong stdout: {stdout.decode()}"
assert stderr.decode() == "error: cannot execute non-executable\n", f"wrong stderr: {stderr.decode()}"

p = subprocess.Popen(["./microshell", "non-executable", ";", "/bin/echo", "hello"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
        )

stdout, stderr = p.communicate();

assert stdout.decode() == "hello\n", f"wrong stdout: {stdout.decode()}"
assert stderr.decode() == "error: cannot execute non-executable\n", f"wrong stderr: {stderr.decode()}"



