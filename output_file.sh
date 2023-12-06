cd test/pepega_tests/ifj23-tests-master && python3 compiler_tests.py

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/compiler_tests.py", line 128, in test_all[0m
[31mcompiler stdin:[0m

        let cycles = 50

        func is_inside(_ real: Double, _ imag: Double) -> Bool {
            var x = real
            var y = imag

            var cycle = 0

            while cycle < cycles {
                let tmp = x
                x = x * x - y * y + real
                y = 2 * tmp * y + imag

                if x * x + y * y > 4 {
                    return false
                } else {}

                cycle = cycle + 1
            }

            return true
        }

        let size = readInt()
        if let size {
            let size_d = Int2Double(size)
            var y = 0 - size
            while y < size {
                var x = 0 - 2 * size

                while x < size {
                    var real = Int2Double(x)
                    var imag = Int2Double(y)
                    real = real / size_d
                    imag = imag / size_d

                    let is_inside = is_inside(real, imag)

                    if is_inside { write() }
                    else { write() }

                    x = x + 1
                }

                write()
                y = y + 1
            }
        } else {
            write("Cannot parse input")
        }

    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $is_inside
DEFVAR LF@%retval
DEFVAR LF@real$1
PUSHS nil@nil
POPS LF@real$1
MOVE LF@real$1 LF@%1
DEFVAR LF@imag$1
PUSHS nil@nil
POPS LF@imag$1
MOVE LF@imag$1 LF@%2
DEFVAR LF@x$2
PUSHS LF@real$1
POPS LF@x$2
DEFVAR LF@y$2
PUSHS LF@imag$1
POPS LF@y$2
DEFVAR LF@cycle$2
PUSHS int@0
POPS LF@cycle$2
DEFVAR LF@tmp$3
PUSHS LF@x$2
POPS LF@tmp$3
LABEL whileStart0
PUSHS LF@cycle$2
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m
