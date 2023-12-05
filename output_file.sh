cd test/pepega_tests/ifj23-tests-master && python3 compiler_tests.py

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/compiler_tests.py", line 55, in test_all[0m
[31mcompiler stdin:[0m

    let input = "ifj projekt je moc hard"
    let mock = mock(input)
    write(mock)

    func is_even(_ i: Int) -> Bool {
        let int = i / 2 * 2 // integer division

        let i_d = Int2Double(i)
        let d = i_d / 2.0 * 2.0
        let double = Double2Int(d)

        return int == double
    }

    func mock_char(_ s: String) -> String {
        var c = ord(s)

        if c >= 65 { if c <= 90 { // big -> small
            c = c + 32
            let new = chr(c)
            return new
        } else {} } else {}

        if c >= 97 { if c <= 122 { // small -> big
            c = c - 32
            let new = chr(c)
            return new
        } else {} } else {}

        return s
    }

    // you know what it is
    func mock(_ s: String) -> String {
        let length = length(s)
        var idx = 0
        var output = ""

        while idx < length {
            let end = idx + 1
            let char_opt = substring(of: s, startingAt: idx, endingBefore: end)
            let char = char_opt!

            let is_even = is_even(idx)

            if is_even {
                let mock_char = mock_char(char)
                output = output + mock_char
            } else {
                output = output + char
            }

            idx = idx + 1
        }

        return output
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $is_even
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
DEFVAR LF@int$1
PUSHS LF@i$1
PUSHS int@2
IDIVS
PUSHS int@2
MULS
POPS LF@int$1
DEFVAR LF@i_d$1
CREATEFRAME
DEFVAR TF@%1
PUSHS LF@i$1
POPS TF@%1
PUSHFRAME
PUSHS LF@%1
INT2FLOATS
POPFRAME
POPS LF@i_d$1
DEFVAR LF@d$1
PUSHS LF@i_d$1
PUSHS float@0x1p+1
DIVS
PUSHS float@0x1p+1
MULS
POPS LF@d$1
DEFVAR LF@double$1
CREATEFRAME
DEFVAR TF@%1
PUSHS LF@d$1
POPS TF@%1
PUSHFRAME
FLOAT2INT GF@tmp_op1 LF@%1
PUSHS GF@tmp_op1
POPFRAME
POPS LF@double$1
PUSHS LF@int$1
PUSHS LF@double$1
EQS
EXIT int@6

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_invalid_return (6)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/compiler_tests.py", line 116, in test_all[0m
[31mcompiler stdin:[0m

    func concat(_ x : String, with y : String) -> String {
        let x = x + y
        return x + " " + y
    }

    let a = "ahoj "
    var ct : String
    ct = concat(a, with: "svete")
    write(ct, a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $concat
DEFVAR LF@%retval
DEFVAR LF@x$1
PUSHS nil@nil
POPS LF@x$1
MOVE LF@x$1 LF@%1
DEFVAR LF@y$1
PUSHS nil@nil
POPS LF@y$1
MOVE LF@y$1 LF@%2
EXIT int@3

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_ident (3)[0m

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
DEFVAR LF@x$1
PUSHS LF@real$1
POPS LF@x$1
DEFVAR LF@y$1
PUSHS LF@imag$1
POPS LF@y$1
DEFVAR LF@cycle$1
PUSHS int@0
POPS LF@cycle$1
LABEL whileStart0
PUSHS LF@cycle$1
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/tokenizer_tests.py", line 5, in test_all[0m
[31mcompiler stdin:[0m

    1.2.3
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
PUSHS float@0x1.3333333333333p+0
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/parser_tests.py", line 25, in test_all[0m
[31mcompiler stdin:[0m

        let result = (2+2(
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS int@2
PUSHS int@2
CREATEFRAME
EXIT int@3

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_ident (3)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/parser_tests.py", line 33, in test_all[0m
[31mcompiler stdin:[0m

        let result = 2<3>4
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS int@2
PUSHS int@3
LTS
PUSHS int@4
GTS
POPS GF@result

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/parser_tests.py", line 34, in test_all[0m
[31mcompiler stdin:[0m

        let result = 2(3+4)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS int@2
CREATEFRAME
EXIT int@3

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_ident (3)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/rec_parser_tests.py", line 9, in test_all[0m
[31mcompiler stdin:[0m

    1.2.3
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
PUSHS float@0x1.3333333333333p+0
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/rec_parser_tests.py", line 14, in test_all[0m
[31mcompiler stdin:[0m
var b
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@b
PUSHS nil@nil
EXIT int@8

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type_inference (8)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/rec_parser_tests.py", line 20, in test_all[0m
[31mcompiler stdin:[0m
if true {}
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
CREATEFRAME
PUSHFRAME
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/rec_parser_tests.py", line 21, in test_all[0m
[31mcompiler stdin:[0m
let a = 5 let b = 4
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@5
POPS GF@a
DEFVAR GF@b
PUSHS int@4
POPS GF@b

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/rec_parser_tests.py", line 22, in test_all[0m
[31mcompiler stdin:[0m
let a: Int let b: Double?
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
DEFVAR GF@b
PUSHS nil@nil
POPS GF@b

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/rec_parser_tests.py", line 23, in test_all[0m
[31mcompiler stdin:[0m
if true {} else {} let a = 5
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
CREATEFRAME
PUSHFRAME
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/rec_parser_tests.py", line 24, in test_all[0m
[31mcompiler stdin:[0m
if true {let a = 5 let b = 3} else {}
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
CREATEFRAME
PUSHFRAME
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/rec_parser_tests.py", line 34, in test_all[0m
[31mcompiler stdin:[0m
a
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/rec_parser_tests.py", line 41, in test_all[0m
[31mcompiler stdin:[0m
_
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 52, in test_all[0m
[31mcompiler stdin:[0m

    let a = 5 // so it begins
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 104, in test_all[0m
[31mcompiler stdin:[0m

    var a: Int?
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
CREATEFRAME
DEFVAR TF@%1
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 121, in test_all[0m
[31mcompiler stdin:[0m

    let a: Int = 5.6
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS float@0x1.6666666666666p+2
FLOAT2INTS
POPS GF@a

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 133, in test_all[0m
[31mcompiler stdin:[0m

    let a = 4
    let b: Double = a
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@4
POPS GF@a
DEFVAR GF@b
PUSHS GF@a
INT2FLOATS
POPS GF@b

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 178, in test_all[0m
[31mcompiler stdin:[0m

    let a: Int
    if true {
        a = 5
    } else { }
    let b = a
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
CREATEFRAME
PUSHFRAME
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 186, in test_all[0m
[31mcompiler stdin:[0m

    let a: Int
    var t = true
    while t {
        a = 5
        t = false
    }
    let b = a
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
DEFVAR GF@t
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 196, in test_all[0m
[31mcompiler stdin:[0m

    var t: Bool
    while t {
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@t
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 202, in test_all[0m
[31mcompiler stdin:[0m

    var t: Bool
    if t {
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@t
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 208, in test_all[0m
[31mcompiler stdin:[0m

    let a: Double
    a = 5
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
PUSHS int@5
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 214, in test_all[0m
[31mcompiler stdin:[0m

    let a: Double? // already initialized to nil
    a = 5
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
PUSHS int@5
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 220, in test_all[0m
[31mcompiler stdin:[0m

    var a: Double? 
    a = 5
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
PUSHS int@5
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 290, in test_all[0m
[31mcompiler stdin:[0m

    let a = 1
    if true {
        write(a)
        let a = "2"
        if true {
            write(a)
            let a = 3
            write(a)
        } else {}
    } else {}
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@1
POPS GF@a
CREATEFRAME
PUSHFRAME
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 312, in test_all[0m
[31mcompiler stdin:[0m

    let a: Bool? = 45 > 3
    if a {
        write(a)
    } else {}
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 373, in test_all[0m
[31mcompiler stdin:[0m

    let a: Int?
    if let a {
        let kentus = a + 4
        let b: Int = a
        write(b)
    } else {
        write(false)
    }
    let b = 5
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
CREATEFRAME
PUSHFRAME
PUSHS nil@nil
PUSHS GF@a
JUMPIFEQS elseJump0
DEFVAR LF@kentus$1
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 390, in test_all[0m
[31mcompiler stdin:[0m

    if let 5 {
    } else {
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
CREATEFRAME
PUSHFRAME
PUSHS nil@nil
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 396, in test_all[0m
[31mcompiler stdin:[0m

    if let nil {
    } else {
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
CREATEFRAME
PUSHFRAME
PUSHS nil@nil
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 410, in test_all[0m
[31mcompiler stdin:[0m

    var a = 5
    while 4 {
        write(a)
        a = a - 1
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@5
POPS GF@a
CREATEFRAME
PUSHFRAME
LABEL whileStart0
PUSHS int@4
PUSHS bool@false
JUMPIFEQS whileEnd0
CREATEFRAME
DEFVAR TF@%1
PUSHS GF@a
POPS TF@%1
PUSHFRAME
WRITE LF@%1
POPFRAME
PUSHS GF@a
PUSHS int@1
SUBS
POPS GF@a
JUMP whileStart0
LABEL whileEnd0
POPFRAME

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 426, in test_all[0m
[31mcompiler stdin:[0m

    func a() {
        while true {
            var a = 5
            write(a)
            return
        }
    }
    a()
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
LABEL whileStart0
PUSHS bool@true
PUSHS bool@false
JUMPIFEQS whileEnd0
DEFVAR LF@a$2
PUSHS int@5
POPS LF@a$2
CREATEFRAME
DEFVAR TF@%1
PUSHS LF@a$2
POPS TF@%1
PUSHFRAME
WRITE LF@%1
POPFRAME
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 437, in test_all[0m
[31mcompiler stdin:[0m

    func a() {
        var t = true
        while t {
            var a = 5
            write(a)
            t = false
        }
    }
    a()
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@t$1
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 449, in test_all[0m
[31mcompiler stdin:[0m

    var t = true
    func a() {
        while t {
            var a = 5
            write(a)
            t = false
        }
    }
    a()
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
LABEL whileStart0
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 461, in test_all[0m
[31mcompiler stdin:[0m

    var t = 5
    func a() {
        while t > 0 {
            var a = 5
            write(t)
            t = t - 1
        }
    }
    a()
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
LABEL whileStart0
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 495, in test_all[0m
[31mcompiler stdin:[0m

    var a = 0
    f1()
    write(" ")
    f1()
    write(" ")
    f1()

    func f1() {
        write("a=", a )
        a = a + 1
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $f1
DEFVAR LF@%retval
CREATEFRAME
DEFVAR TF@%1
PUSHS string@a=
POPS TF@%1
DEFVAR TF@%2
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 509, in test_all[0m
[31mcompiler stdin:[0m

    if true {
        func a() {}
    } else {}
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
RETURN
LABEL $$main
CREATEFRAME
PUSHFRAME
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 515, in test_all[0m
[31mcompiler stdin:[0m

    func a() {
        func b() {}
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 521, in test_all[0m
[31mcompiler stdin:[0m

    func a() {
        func a() {}
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 527, in test_all[0m
[31mcompiler stdin:[0m

    func a() {}
    func a() {}
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
RETURN
EXIT int@3

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_ident (3)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 537, in test_all[0m
[31mcompiler stdin:[0m

    var a = 1
    var b: Int?
    func copy() {
        b = a
    }
    copy()
    write(b, " ")

    a = 2
    copy()
    write(b)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $copy
DEFVAR LF@%retval
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 552, in test_all[0m
[31mcompiler stdin:[0m
func abc(a a: Int) {}
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $abc
DEFVAR LF@%retval
DEFVAR LF@a$1
PUSHS nil@nil
POPS LF@a$1
MOVE LF@a$1 LF@%1
RETURN
LABEL $$main

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 554, in test_all[0m
[31mcompiler stdin:[0m

    // mutual recursion

    func a(_ i: Int) {
        write("a: ", i, " ")
        let decrement = i - 1

        if decrement >= 0 {
            b(decrement)
        } else {}
    }

    func b(_ i: Int) {
        write("b: ", i, " ")
        let decrement = i - 1

        if decrement >= 0 {
            a(decrement)
        } else {}
    }

    a(4)
    b(4)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
CREATEFRAME
DEFVAR TF@%1
PUSHS string@a:\032
POPS TF@%1
DEFVAR TF@%2
PUSHS LF@i$1
POPS TF@%2
DEFVAR TF@%3
PUSHS string@\032
POPS TF@%3
PUSHFRAME
WRITE LF@%1
WRITE LF@%2
WRITE LF@%3
POPFRAME
DEFVAR LF@decrement$1
PUSHS LF@i$1
PUSHS int@1
SUBS
POPS LF@decrement$1
PUSHS LF@decrement$1
PUSHS int@0
LTS
NOTS
PUSHS bool@false
JUMPIFEQS elseJump0
CREATEFRAME
EXIT int@3

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_ident (3)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 579, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ a: Int) {}
    a()
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@a$1
PUSHS nil@nil
POPS LF@a$1
MOVE LF@a$1 LF@%1
RETURN
LABEL $$main
CREATEFRAME
PUSHFRAME
CALL $a
POPFRAME

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 589, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ a: Int) {}
    let value: Int? = 4
    a(value)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@a$1
PUSHS nil@nil
POPS LF@a$1
MOVE LF@a$1 LF@%1
RETURN
LABEL $$main
DEFVAR GF@value
PUSHS int@4
POPS GF@value
CREATEFRAME
DEFVAR TF@%1
PUSHS GF@value
POPS TF@%1
PUSHFRAME
CALL $a
POPFRAME

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 623, in test_all[0m
[31mcompiler stdin:[0m

    func a() { c() }
    func c() { b() }
    func b() { a() }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
CREATEFRAME
EXIT int@3

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_ident (3)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 629, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ i: Int, param j: Double?) { c(i, param: j) }
    func c(_ i: Int, param j: Double?) { b(i, param: j) }
    func b(_ i: Int, param j: Double?) { a(i, param: j) }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
DEFVAR LF@j$1
PUSHS nil@nil
POPS LF@j$1
MOVE LF@j$1 LF@%2
CREATEFRAME
EXIT int@3

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_ident (3)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 635, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ i: Int) { c(i) }
    func c(_ i: Int) { b(i) }
    func b(_ i: Int) { a(i) }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
CREATEFRAME
EXIT int@3

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_ident (3)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 646, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ i: Int?) {}
    a(nil)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
RETURN
LABEL $$main
CREATEFRAME
DEFVAR TF@%1
PUSHS nil@nil
EXIT int@4

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_call (4)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 661, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ i: Int?) {}
    a()
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
RETURN
LABEL $$main
CREATEFRAME
PUSHFRAME
CALL $a
POPFRAME

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 672, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ i: Int?) {}
    let a: Int?
    a(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
RETURN
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
CREATEFRAME
DEFVAR TF@%1
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 683, in test_all[0m
[31mcompiler stdin:[0m

    func a(i _: Int?) {}
    a(i: nil)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 688, in test_all[0m
[31mcompiler stdin:[0m

    func a(i _: Int?) {}
    a(i: 4)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 693, in test_all[0m
[31mcompiler stdin:[0m

    func a(i _: Int) {}
    a(i: 4)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 698, in test_all[0m
[31mcompiler stdin:[0m

    func a(i _: Int) {}
    a(i: nil)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 703, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ _: Int) {}
    a(4)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 708, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ _: Int) {}
    a(nil)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 713, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ _: Int) {}
    a(4.5)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 718, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ i: Int) {
        write(i, " ")
        let i = "kentus"
        write(i)
    }
    a(42)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
CREATEFRAME
DEFVAR TF@%1
PUSHS LF@i$1
POPS TF@%1
DEFVAR TF@%2
PUSHS string@\032
POPS TF@%2
PUSHFRAME
WRITE LF@%1
WRITE LF@%2
POPFRAME
EXIT int@3

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_ident (3)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 727, in test_all[0m
[31mcompiler stdin:[0m

    func a(kentus i: Int) { }
    a(42)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
RETURN
LABEL $$main
CREATEFRAME
DEFVAR TF@%1
PUSHS int@42
POPS TF@%1
EXIT int@4

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_call (4)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 732, in test_all[0m
[31mcompiler stdin:[0m

    func a(_ i: Int) { }
    a(kentus: 42)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
DEFVAR LF@i$1
PUSHS nil@nil
POPS LF@i$1
MOVE LF@i$1 LF@%1
RETURN
LABEL $$main
CREATEFRAME
EXIT int@4

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_call (4)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 776, in test_all[0m
[31mcompiler stdin:[0m

    func a() -> Int {
        if true {
            return "kentus"
        } else {}
    }
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 792, in test_all[0m
[31mcompiler stdin:[0m

    func a() -> String {
        while true {
            return "kentus"
        }
    }
    let a = a()
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
LABEL whileStart0
PUSHS bool@true
PUSHS bool@false
JUMPIFEQS whileEnd0
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 802, in test_all[0m
[31mcompiler stdin:[0m

    func a() -> Int {
        if true {
            let a = 5
            if true { return 1
            } else { return 5}
        } else {
            return 2
        }

        while true {
            if true { return 3
            } else { return 4 }
            return 5
        }
    }
    let a = a()
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 822, in test_all[0m
[31mcompiler stdin:[0m

    func a() -> Int {
        if true {
            let a = 5
            if true { return 1
            } else {/*here it's missing*/}
        } else {
            return 2
        }

        while true {
            if true { return 3
            } else { return 4 }
            return 5
        }
    }
    let a = a()
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 842, in test_all[0m
[31mcompiler stdin:[0m

    func a() -> String {
        if true {
            return "kentus"
        } else {}
    }
    let a = a()
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 893, in test_all[0m
[31mcompiler stdin:[0m

    func a() -> Int? {
        return nil
    }
    let a = a()
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
PUSHS nil@nil
EXIT int@4

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_call (4)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 901, in test_all[0m
[31mcompiler stdin:[0m

    func a() -> Double {
        return 4
    }
    let a = a()
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
PUSHS int@4
EXIT int@4

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_call (4)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 909, in test_all[0m
[31mcompiler stdin:[0m

    func a() -> Double? {
        return 4
    }
    let a = a()
    write(a)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $a
DEFVAR LF@%retval
PUSHS int@4
EXIT int@4

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_call (4)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 946, in test_all[0m
[31mcompiler stdin:[0m

    if true {
        return 4
    } else {}
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
CREATEFRAME
PUSHFRAME
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 975, in test_all[0m
[31mcompiler stdin:[0m

    let a = 5
    let b = a - nil
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@5
POPS GF@a
DEFVAR GF@b
PUSHS GF@a
PUSHS nil@nil
SUBS
POPS GF@b

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 980, in test_all[0m
[31mcompiler stdin:[0m

    let a: Int? = 5
    let b: Int? = 2
    let c = a - b
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@5
POPS GF@a
DEFVAR GF@b
PUSHS int@2
POPS GF@b
DEFVAR GF@c
PUSHS GF@a
PUSHS GF@b
SUBS
POPS GF@c

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 986, in test_all[0m
[31mcompiler stdin:[0m

    let a: Int? = 5
    let b = a - 7
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@5
POPS GF@a
DEFVAR GF@b
PUSHS GF@a
PUSHS int@7
SUBS
POPS GF@b

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1003, in test_all[0m
[31mcompiler stdin:[0m

        let result =  "abc" - "def" 
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS string@abc
PUSHS string@def
SUBS
POPS GF@result

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1010, in test_all[0m
[31mcompiler stdin:[0m

    let a: Int? = 5
    let b = a ?? nil
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@5
POPS GF@a
DEFVAR GF@b
PUSHS GF@a
PUSHS nil@nil
POPS GF@tmp_op2
POPS GF@tmp_op1
JUMPIFNEQ %left_op$0 nil@nil GF@tmp_op1
PUSHS GF@tmp_op2
JUMP %right_op$0
LABEL %left_op$0
PUSHS GF@tmp_op1
LABEL %right_op$0
POPS GF@b

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1015, in test_all[0m
[31mcompiler stdin:[0m

    let a: String?
    let b = 4
    let c = a ?? b
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
DEFVAR GF@b
PUSHS int@4
POPS GF@b
DEFVAR GF@c
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1021, in test_all[0m
[31mcompiler stdin:[0m

    let a: String?
    let b = "abc"
    let c = b ?? a
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
DEFVAR GF@b
PUSHS string@abc
POPS GF@b
DEFVAR GF@c
PUSHS GF@b
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1032, in test_all[0m
[31mcompiler stdin:[0m

    let a: Int? // nil initialization
    let b = a ?? 4
    write(b)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
DEFVAR GF@b
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1055, in test_all[0m
[31mcompiler stdin:[0m

    let a: Int?
    let b = 4 + a! + 4
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
DEFVAR GF@b
PUSHS int@4
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1060, in test_all[0m
[31mcompiler stdin:[0m

    let a: String?
    let b = 4 + a! + 4
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
DEFVAR GF@b
PUSHS int@4
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1065, in test_all[0m
[31mcompiler stdin:[0m

    let a: String?
    let b = "b" + a!
    write(b)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
DEFVAR GF@b
PUSHS string@b
EXIT int@5

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_undefined_var (5)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1071, in test_all[0m
[31mcompiler stdin:[0m

        let result = nil!
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS nil@nil
EXIT int@8

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type_inference (8)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1111, in test_all[0m
[31mcompiler stdin:[0m

        let result = 
    "abc" != nil
    
        write(result)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1122, in test_all[0m
[31mcompiler stdin:[0m

        let result = nil >= nil
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS nil@nil
PUSHS nil@nil
LTS
NOTS
POPS GF@result

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1125, in test_all[0m
[31mcompiler stdin:[0m

        let result = nil <= 4
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS nil@nil
PUSHS int@4
GTS
NOTS
POPS GF@result

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1127, in test_all[0m
[31mcompiler stdin:[0m

        let result =  "abc" <= nil 
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS string@abc
PUSHS nil@nil
GTS
NOTS
POPS GF@result

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1132, in test_all[0m
[31mcompiler stdin:[0m

        let result = nil <= 4
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS nil@nil
PUSHS int@4
GTS
NOTS
POPS GF@result

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1134, in test_all[0m
[31mcompiler stdin:[0m

    let a: Double? = nil
    let b = 3.2
    let c = a > b
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS nil@nil
POPS GF@a
DEFVAR GF@b
PUSHS float@0x1.999999999999ap+1
POPS GF@b
DEFVAR GF@c
PUSHS GF@a
PUSHS GF@b
GTS
POPS GF@c

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1140, in test_all[0m
[31mcompiler stdin:[0m

    let a: Double? = 4
    let b = 3.2
    let c = a > b
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@4
INT2FLOATS
POPS GF@a
DEFVAR GF@b
PUSHS float@0x1.999999999999ap+1
POPS GF@b
DEFVAR GF@c
PUSHS GF@a
PUSHS GF@b
GTS
POPS GF@c

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1248, in test_all[0m
[31mcompiler stdin:[0m

        let result = "abc#def"
        write(result)
    
[31mcompiler stdout:[0m
.IFJcode23

EXIT 1

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_lexer (1)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1250, in test_all[0m
[31mcompiler stdin:[0m

        let result = true
        write(result)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS bool@true
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1251, in test_all[0m
[31mcompiler stdin:[0m

        let result = false
        write(result)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
PUSHS bool@false
EXIT int@7

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_type (7)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1253, in test_all[0m
[31mcompiler stdin:[0m

        let result =  "\u{1}\u{37}\u{71}\u{7e}\u{7f}"
        write(result)
    
[31mcompiler stdout:[0m
.IFJcode23

EXIT 1

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_lexer (1)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1255, in test_all[0m
[31mcompiler stdin:[0m

    let a = 45
    let b = 2.3
    let c: Bool? = nil
    let d = "\n"
    write(a, " kentus ", a, d, b, c, " ", d )
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@a
PUSHS int@45
POPS GF@a
DEFVAR GF@b
PUSHS float@0x1.2666666666666p+1
POPS GF@b
DEFVAR GF@c
EXIT int@2

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_parser (2)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1282, in test_all[0m
[31mcompiler stdin:[0m

        let result = length("\u{123}")
        write(result)
    
[31mcompiler stdout:[0m
.IFJcode23

EXIT 1

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_lexer (1)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1330, in test_all[0m
[31mcompiler stdin:[0m
 substring("123456789", startingAt: 4, endingBefore: 4) 
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
CREATEFRAME
DEFVAR TF@%1
PUSHS string@123456789
POPS TF@%1
DEFVAR TF@%2
PUSHS int@4
POPS TF@%2
DEFVAR TF@%3
PUSHS int@4
POPS TF@%3
PUSHFRAME
LT GF@tmp_op1 LF@%2 int@0
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
LT GF@tmp_op1 LF@%3 int@0
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
JUMPIFEQ %substringNil$0 LF@%3 LF@%2
LT GF@tmp_op1 LF@%3 LF@%2
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
STRLEN GF@tmp_op2 LF@%1
GT GF@tmp_op1 LF@%3 GF@tmp_op2
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
STRLEN GF@tmp_op2 LF@%1
JUMPIFEQ %substringNil$0 GF@tmp_op2 LF@%2
GT GF@tmp_op1 LF@%2 GF@tmp_op2
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
PUSHS string@
POPS GF@tmp_op1
LABEL %substring$0
PUSHS LF@%2
PUSHS LF@%3
JUMPIFEQS %substringEnd$0
GETCHAR GF@tmp_op2 LF@%1 LF@%2
CONCAT GF@tmp_op1 GF@tmp_op1 GF@tmp_op2
ADD LF@%2 LF@%2 int@1
JUMP %substring$0
LABEL %substringEnd$0
PUSHS GF@tmp_op1
JUMP  %substringEndFinal$0
LABEL %substringNil$0
PUSHS nil@nil
LABEL %substringEndFinal$0
POPFRAME

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: interpreter failed with exit code 58[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1343, in test_all[0m
[31mcompiler stdin:[0m

        let result = ord("")
        write(result)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
DEFVAR GF@result
CREATEFRAME
DEFVAR TF@%1
PUSHS string@
POPS TF@%1
PUSHFRAME
PUSHS LF@%1
PUSHS int@0
STRI2INTS
POPFRAME
POPS GF@result
CREATEFRAME
DEFVAR TF@%1
PUSHS GF@result
POPS TF@%1
PUSHFRAME
WRITE LF@%1
POPFRAME

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m
[31mexpected output:[0m
0
[31minterpreter stdout:[0m

[31minterp_stderr:[0m
Error at line: 16
String index out of bounds!


[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1345, in test_all[0m
[31mcompiler stdin:[0m

        let result = ord("\u{bA}")
        write(result)
    
[31mcompiler stdout:[0m
.IFJcode23

EXIT 1

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_lexer (1)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1346, in test_all[0m
[31mcompiler stdin:[0m

        let result = ord("#")
        write(result)
    
[31mcompiler stdout:[0m
.IFJcode23

EXIT 1

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.error_lexer (1)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1361, in test_all[0m
[31mcompiler stdin:[0m
chr()
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
CREATEFRAME
PUSHFRAME
PUSHS LF@%1
INT2CHARS
POPFRAME

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

[31;1mError: compiler return code does not match expected value[0m
[33m  File "/mnt/c/programming/IFJ/IFJCompiler/test/pepega_tests/ifj23-tests-master/backend_tests.py", line 1365, in test_all[0m
[31mcompiler stdin:[0m

    substring(of: "123456789", startingAt: 0)
    
[31mcompiler stdout:[0m
.IFJcode23

DEFVAR GF@tmp_op1
DEFVAR GF@tmp_op2
DEFVAR GF@tmp_op3
JUMP $$main
LABEL $$main
CREATEFRAME
DEFVAR TF@%1
PUSHS string@123456789
POPS TF@%1
DEFVAR TF@%2
PUSHS int@0
POPS TF@%2
PUSHFRAME
LT GF@tmp_op1 LF@%2 int@0
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
LT GF@tmp_op1 LF@%3 int@0
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
JUMPIFEQ %substringNil$0 LF@%3 LF@%2
LT GF@tmp_op1 LF@%3 LF@%2
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
STRLEN GF@tmp_op2 LF@%1
GT GF@tmp_op1 LF@%3 GF@tmp_op2
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
STRLEN GF@tmp_op2 LF@%1
JUMPIFEQ %substringNil$0 GF@tmp_op2 LF@%2
GT GF@tmp_op1 LF@%2 GF@tmp_op2
JUMPIFEQ %substringNil$0 GF@tmp_op1 bool@true
PUSHS string@
POPS GF@tmp_op1
LABEL %substring$0
PUSHS LF@%2
PUSHS LF@%3
JUMPIFEQS %substringEnd$0
GETCHAR GF@tmp_op2 LF@%1 LF@%2
CONCAT GF@tmp_op1 GF@tmp_op1 GF@tmp_op2
ADD LF@%2 LF@%2 int@1
JUMP %substring$0
LABEL %substringEnd$0
PUSHS GF@tmp_op1
JUMP  %substringEndFinal$0
LABEL %substringNil$0
PUSHS nil@nil
LABEL %substringEndFinal$0
POPFRAME

[31mcompiler stderr:[0m

[31mcompiler returned error code ErrorType.success (0)[0m

103 tests failed
