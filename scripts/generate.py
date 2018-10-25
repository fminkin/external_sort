#!/usr/bin/python3
# -*- coding: utf-8 -*-
import argparse
import io
import random
import string


def _parse_args():
    parser = argparse.ArgumentParser(description='Generates file '
                                                 'with randomly sampled strings')
    parser.add_argument(
        '--output',
        help='output filepath'
    )
    parser.add_argument(
        '--lines_count',
        type=int,
        help='lines count'
    )
    parser.add_argument(
        '--max_length',
        type=int,
        help='max line length'
    )

    return parser.parse_args()

def generate_random_string(max_length):
    return ''.join(random.choices(string.ascii_lowercase +\
                                  string.ascii_uppercase +\
                                  string.digits, k=max_length))

def _main(args):
    with io.open(args.output, 'w', encoding='utf-8') as fout:
        for _ in range(args.lines_count):
            length = random.randint(0, args.max_length)
            fout.write(generate_random_string(length) + '\n')

if __name__ == '__main__':
    _main(_parse_args())
