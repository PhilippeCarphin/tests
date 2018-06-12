import csv
with open('in.csv') as csv_in:
    reader = csv.reader(
            csv_in,
            delimiter=','
    )
    with open('out.csv', 'w') as csv_out:
        writer = csv.writer(
                csv_out,
                delimiter=','
                #quotechar=
                #quoting=csv.QUOTE_MINIMAL
        )
        for row in reader:
            # if is_grade_row(row)
                # group = group_from_row(row)
                # grage = get_group_grade(group)
                # commnt = get_group_comment(group)
                # new_row = make_new_row(row, grade, comment)
            # else
                # new_row = row
            # writer.writerow(new_row)

            new_row = row[:2] + [' a'] + row[3:]
            writer.writerow(new_row)

GROUP_COLUMN = 3
def is_grade_row(row):
    return row[GROUP_COLUMN].startswith('Groupe_')

def find_group_file(group):
    return './group/correction' + group + '.csv'

def get_group_info(filepath)
    # with open(filepath) as notes
    # grade
    # comment
    # return { 'grade' : grade, 'comment' : comment}
    return {'grade': 22, 'comment': 'bonjour'}

def makd_new_row(row, grade, comment):
    return row[:GRADE_COLUMN] + [grade] + row[(GRADE_COLUMN+1):]

