#!/usr/bin/python3
# -*- coding: utf-8 -*-
import argparse
import io


def _parse_args():
    parser = argparse.ArgumentParser(description='Checks if file is sorted. '
                                                 'Compares length, if source is given')
    parser.add_argument(
        '--result',
        help='sorting result file filepath'
    )
    parser.add_argument(
        '--source',
        default=None,
        help='source, unsorted file'
    )

    return parser.parse_args()

def _main(args):

    with io.open(args.result, 'r', encoding='utf-8') as fin:
        lines = list(map(str.strip, fin.readlines()))

    if args.source:
        with io.open(args.source, 'r', encoding='utf-8') as fin:
            source_lines = fin.readlines()
        if len(source_lines) != len(lines):
            print('Failed, file contains {} lines, '
                  'but must contain {} lines'.format(len(lines), len(source_lines)))
        else:
            print('Ok, line count matches')

        if sorted(map(str.strip, source_lines)) != lines:
            print('Failed, external sort result does not match default sorting result')
        else:
            print('Ok, external sort result matches default sorting result')
    else:
        previous_line = lines[0]
        for line in lines[1:]:
            if line < previous_line:
                print('Failed, resulting file is unsorted')
                exit(1)
            previous_line = line
        print('Ok, resulting file is sorted, consistency with '
              'source is not checked, specify --source argument')


if __name__ == '__main__':
    _main(_parse_args())
