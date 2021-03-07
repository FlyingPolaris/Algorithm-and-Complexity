import tkinter
from tkinter import messagebox

window = tkinter.Tk()
window.title('Drawing')
window.geometry('600x400')

inputer = tkinter.Entry(window, width=5, show=None, highlightcolor='red', highlightthickness=1)
inputer.pack()

inputlabel = tkinter.Label(window, text='Please input a valid integer from 1 to 10', font='System')
inputlabel.pack()
num = 0
cv = tkinter.Canvas(window, bg='white')
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


def create_line():
    global num

    for i in range(1, num + 1):
        line_point = [(20, 20 + 20 * i), (360, 20 + 20 * i)]
        cv.create_line(line_point, fill='black', width=2)
        if not i == 1:
            shortlinenum = num - i + 1
            if shortlinenum % 2 == 1:
                p1 = (190, 20 * i)
                p2 = (190, 20 + 20 * i)
                paintshortline(p1, p2)
                for j in range(1, int(shortlinenum / 2 + 1)):
                    p1 = (190 - 40 * j, 20 * i)
                    p2 = (190 - 40 * j, 20 + 20 * i)
                    p3 = (190 + 40 * j, 20 * i)
                    p4 = (190 + 40 * j, 20 + 20 * i)
                    paintshortline(p1, p2)
                    paintshortline(p3, p4)
            else:
                for j in range(1, int(shortlinenum / 2 + 1)):
                    p1 = (210 - 40 * j, 20 * i)
                    p2 = (210 - 40 * j, 20 + 20 * i)
                    p3 = (170 + 40 * j, 20 * i)
                    p4 = (170 + 40 * j, 20 + 20 * i)
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
        if num > 10:
            messagebox.showwarning('Warning', 'The number is too big!(Please input a valid integer from 1 to 10)')
            inputer.delete(0, 'end')
            catch_num()
        elif num <= 0:
            messagebox.showwarning('Warning', 'The number is too small!(Please input a valid integer from 1 to 10)')
            inputer.delete(0, 'end')
            catch_num()
    except:
        messagebox.showwarning('Warning', 'Not a valid integer!(Please input a valid integer from 1 to 10)')
        inputer.delete(0, 'end')
        catch_num()
    create_line()


button = tkinter.Button(window, text='Draw', width=10, height=1, command=(lambda: catch_num()))
button.pack()

window.mainloop()
