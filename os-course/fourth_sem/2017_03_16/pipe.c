int main()
{
	int pipefd[2];
	int r = pipe(pipefd);
	if (r == -1)
		return EXIT_FAILURE;
	int pid = fork();
	if (!pid)
		dup2(pipefd[0], STDIN_FILENO);
	else
		dup2(pipefd[1], STDOUT_FILENO);
	int offset = 0;
	char buf[4096];
	while (1)
	{
		r = read(STRING_FILENO, buf + offset, sizeof(buf) - offset);
		if (!r)
			return EXIT_SUCCESS;
		offset += r;
		r = write(STDOUT_FILENO, buf, offset);
		memmove(buf, buf + r, offset - r);
		offset -= r;
	}
	return EXIT_SUCCESS;
}