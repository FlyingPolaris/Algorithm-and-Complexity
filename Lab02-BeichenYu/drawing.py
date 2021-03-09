import tkinter
from tkinter import messagebox

window = tkinter.Tk()
window.title('Drawing')
window.geometry('1000x600')

inputer = tkinter.Entry(window, width=5, show=None, highlightcolor='red', highlightthickness=1)
inputer.pack()

inputlabel = tkinter.Label(window, text='(Please input a valid positive integer)', font='System')
inputlabel.pack()
num = 0
cv = tkinter.Canvas(window, bg='white', height=600 * 0.8, width=960)
# cv.create_rectangle(10, 10, 110, 110)
cv.pack()


def clearall():
    cv.delete(tkinter.ALL)


def paintpoint(p1):
    x1, y1 = (p1[0] - 3), (p1[1] - 3)
    x2, y2 = (p1[0] + 3), (p1[1] + 3)
    cv.create_oval(x1, y1, x2, y2, fill='black')


def paintshortline(p1, p2):
    paintpoint(p1)
    paintpoint(p2)
    shortline_point = [p1, p2]
    cv.create_line(shortline_point, fill='black', width=2)


def paintlongline(p1, p2):
    cv.create_line([p1, p2], fill='black', width=2)


def create_line():
    global num
    up = 20
    down = 600 * 0.8 - 20
    left = 20
    right = 960 - 20
    mid = (left + right) / 2
    # paintlongline((left, 20), (right, 20))
    # paintlongline((left, up), (left, down))
    if num == 1:
        paintlongline((left, (up + down) / 2), (right, (up + down) / 2))
        return
    for i in range(1, num + 1):
        dis = (down - up) / (num - 1)
        left_point = (left, up + dis * (i - 1))
        right_point = (right, up + dis * (i - 1))
        paintlongline(left_point, right_point)
        if i == num:
            continue
        shortlinenum = num - i
        if shortlinenum % 2 == 1:
            p1 = (mid, up + dis * (i - 1))
            p2 = (mid, up + dis * i)
            paintshortline(p1, p2)
            for j in range(1, int(shortlinenum / 2 + 1)):
                p1 = (mid - 2 * dis * j, up + dis * (i - 1))
                p2 = (mid - 2 * dis * j, up + dis * i)
                p3 = (mid + 2 * dis * j, up + dis * (i - 1))
                p4 = (mid + 2 * dis * j, up + dis * i)
                paintshortline(p1, p2)
                paintshortline(p3, p4)
        else:
            for j in range(1, int(shortlinenum / 2 + 1)):
                p1 = (mid + dis - 2 * dis * j, up + dis * (i - 1))
                p2 = (mid + dis - 2 * dis * j, up + dis * i)
                p3 = (mid - dis + 2 * dis * j, up + dis * (i - 1))
                p4 = (mid - dis + 2 * dis * j, up + dis * i)
                paintshortline(p1, p2)
                paintshortline(p3, p4)


def catch_num():
    clearall()
    global num
    var = inputer.get()
    if var == '':
        num = 0
        return
    try:
        num = int(var)
        # if num > 10:
        #     messagebox.showwarning('Warning', 'The number is too big!(Please input a valid integer from 1 to 10)')
        #     inputer.delete(0, 'end')
        #     catch_num()
        if num <= 0:
            messagebox.showwarning('Warning',
                                   'You can\'t input a negative number! Please input a valid positive integer')
            inputer.delete(0, 'end')
            catch_num()
    except:
        messagebox.showwarning('Warning',
                               'Not a valid integer! Please input a valid positive integer')
        inputer.delete(0, 'end')
        catch_num()
    create_line()


button = tkinter.Button(window, text='Draw', width=10, height=1, command=(lambda: catch_num()))
button.pack()

window.mainloop()
