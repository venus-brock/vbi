## VBI

VBI is an interpreter for Befunge-93 which is "mostly" spec compliant. Unlike
the reference implementation of Befunge-93, the stack int size is 64 bit
regardless of platform. Aside from this distinction, if you are aware of any
program which behaves differently on VBI from how it does on the reference
interpreter, I'd love to hear about it. Shoot me an email at venus@brock-v.dev

VBI is short for "Venus Befunge-93 Interpreter". Real imaginative, eh?

### Building VBI

Run the following

```shell
git clone https://github.com/venus-brock/vbi
cd vbi
make
```

The executable will be placed at bin/vbi.

### Running the examples

To run the example programs, first build the project, then run
`bin/vbi eg/<filename>`

### About

VBI was originally written as a practice project for programming in C, but in
the process of creating it I have become enamored with the Befunge-93 language.
As a consequence, I now have more related projects planned. What a nightmare.

Read the full Befunge-93 spec here:
https://catseye.tc/view/befunge-93/doc/Befunge-93.markdown

todo:
create a better interface  
ETA when I feel like it
