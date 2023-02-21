# randomname

randomname is a program (and library) that generates random names.

If you often need to create somewhat transient things with names that
are easy to remember, like I do, you may find this helpful.

randomname can output names with 1 to 3 parts that are randomly chosen
from lists of adjectives, animals, colors, periodic table elements,
notable people, nouns and numbers.

## Examples

The default output is a 2-part name in the form of `adjective-noun`.
Example:

```
$ randomname
sharp-proposal
```

There are presets for creating names that sound like Ubuntu releases,
docker containers (the list of adjectives and notable persons are
taken straight from the docker project) and heroku instances:

```
$ randomname --ubuntu
happy-hapuku
$ randomname --docker
relaxed_carson
$ randomname --heroku
unarmed-business-6349
```

but you can also specify options to adjust the output to your liking:

```
$ randomname --left color --middle element --right number
auburn-carbon-6428
$ randomname --left color --left-start a --right animal --right-start b
amber-bonobo
$ randomname --separator : --right color
clever:bittersweet-shimmer
```

Here is the help output so you can have an idea of all available
options:

```
$ randomname --help
randomname - a random name generator
Usage: randomname [options]

Options:
  -l, --left=WORDLIST          What to use for the left part of the name.
                               See word lists below. Default: adjective
  -m, --middle=WORDLIST        What to use for the middle part of the name.
                               See word lists below. Default: none
  -r, --right=WORDLIST         What to use for the right part of the name.
                               See word lists below. Default: noun
      --left-start=LETTER      The 1st letter of the left word (a-z).
      --middle-start=LETTER    The 1st letter of the middle word (a-z).
      --right-start=LETTER     The 1st letter of the right word (a-z).
  -s, --separator=SEPARATOR    The separator to use between words. Default: '-'
                               Place separator inside quotes if it's a special
                               character that may be interpreted by your shell.
      --no-dashes              Do not allow words with dashes (e.g. bite-sized).
      --docker                 Create names like docker containers.
      --heroku                 Create names like heroku.
      --ubuntu[=LETTER]        Create names that sound like Ubuntu releases.
                               You can optionally specify the 1st letter to use.

Word lists:
  none                         Do not use this part of the name.
  adjective                    A list of adjectives.
  adjective-docker             A smaller list of adjectives as used by docker.
  animal                       A list of animals.
  color                        A list of colors.
  element                      A list of periodic table elements.
  noun                         A list of nouns.
  number                       A four-digit number.
  person                       A list of notable people as used by docker.

Help options:
  -h, --help                   Show this help message.
```

## librandomname library

Look into the `librandomname.h` header file for functions that you may
use to create random names in your own programs.

## Installation

This project uses [meson](https://mesonbuild.com/) for compilation and
installation. You can use something like the following from the
top-level directory of the source code:

```
mkdir build
meson setup build
meson compile -C build
meson install -C build
```

You may use the `--help` options with any one of the meson commands to
show the available options:

```
meson setup --help
meson compile --help
meson install --help
```

