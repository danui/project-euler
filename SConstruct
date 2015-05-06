env = Environment()

util_o = env.Object('util.c')
words_o = env.Object('words.c');

sudoku_env = Environment()
sudoku_env['CFLAGS'] = ['-Isudoku', '-I.', '-O3']
sudoku_objs = [
	sudoku_env.Object('sudoku/sudoku.c'),
	sudoku_env.Object('sudoku/sudoku_slot.c'),
	sudoku_env.Object('sudoku/sudoku_group.c'),
];

env.Program('out/problem-8', 'problem-8.c')
env.Program('out/problem-31', 'problem-31.c')
env.Program('out/problem-48', 'problem-48.c')
env.Program('out/problem-50', ['problem-50.c', util_o])
env.Program('out/problem-23', 'problem-23.c')
env.Program('out/problem-25', 'problem-25.c')
env.Program('out/problem-43', 'problem-43.c')
env.Program('out/test_is_prime', ['test_is_prime.c', util_o])
env.Program('out/random_prime', ['random_prime.c', util_o])
env.Program('out/problem-26', ['problem-26.c', util_o])
env.Program('out/problem-52', ['problem-52.c', util_o])
env.Program('out/problem-59', ['problem-59.c', words_o])
env.Program('out/problem-96', ['problem-96.c'] + sudoku_objs)
env.Program('out/problem-96-brute-force', ['problem-96-brute-force.c'])
env.Program('out/problem-67', ['problem-67.c'])
env.Program('out/problem-97', ['problem-97.c'])
env.Program('out/problem-103', ['problem-103.c'])
