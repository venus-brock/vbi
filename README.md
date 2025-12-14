## VBI

VBI is an interpreter for Befunge-93 which aims to be as closely compliant to
the language specification as possible. No Befunge-98-specific instructions are
supported. Unlike the reference implementation of Befunge-93, unsupported
instructions are treated as whitespace.

VBI is short for "Venus Befunge-93 Interpreter". Real imaginative, eh?

### Building VBI

Run the following

```shell
git clone https://github.com/venus-brock/vbi
cd vbi
mkdir bin
make
```

### Running the examples

To run the example programs, first build the project, then run
`bin/vbi eg/<filename>`

### About

VBI was written as a personal project to become more familiar with using C with
the standard library and using C-style pointers. Any issues will likely be
ignored except those related to compliance with the language specification.

Read the full Befunge-93 spec here:
https://catseye.tc/view/befunge-93/doc/Befunge-93.markdown

todo:
create a better interface  
ETA when I feel like it
