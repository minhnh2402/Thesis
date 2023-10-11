function varargout = GUI_DeltaRobot(varargin)

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI_DeltaRobot_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI_DeltaRobot_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before GUI_DeltaRobot is made visible.
function GUI_DeltaRobot_OpeningFcn(hObject, eventdata, handles, varargin)



%/////////////////do thi///////////////////

%KHOI TAO TEN DO THI
axes(handles.axes1);
title('','Color',[0 0 0],'FontSize',10); 
            xlabel('X','Color',[1 0 0]);
            ylabel('Y','Color',[0 1 0]);
            zlabel('Z','Color',[0 0 1]);

handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes GUI_DeltaRobot wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = GUI_DeltaRobot_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
ModelName = 'AssemRobot_Matlab';
global var;

%theta1
theta1= get(handles.slider1,'value');
set(handles.edit1,'string',num2str(theta1));

%theta2
theta2= get(handles.slider2,'value');
set(handles.edit2,'string',num2str(theta2));

%theta3
theta3= get(handles.slider3,'value');
set(handles.edit3,'string',num2str(theta3));

%////////////////////////////////////////////////////////////
set_param([ModelName '/Gain'],'Gain',num2str(theta1));
set_param([ModelName '/Gain1'],'Gain',num2str(theta2));
set_param([ModelName '/Gain2'],'Gain',num2str(theta3));

%Forward Kinematics

L = 150;
l = 344;
d = 40;
wb = 112;
wp = 60;
a = wp - wb; % -52
b = -sqrt(3)/2*a;
c = -0.5*a;

x1 = 0
x2 = -(sqrt(3)/2*L*cosd(theta2) + b)
x3 = (sqrt(3)/2*L*cosd(theta3) + b)

y1 = (L*cosd(theta1) - a)
y2 = -(0.5*L*cosd(theta2) + c)
y3 = -(0.5*L*cosd(theta3) + c)

z1 = L*sind(theta1) + d
z2 = L*sind(theta2) + d
z3 = L*sind(theta3) + d

dnm = (y2-y1)*x3-(y3-y1)*x2;
 
w1 = y1*y1 + z1*z1;
w2 = x2*x2 + y2*y2 + z2*z2;
w3 = x3*x3 + y3*y3 + z3*z3;

a1 = (z2-z1)*(y3-y1)-(z3-z1)*(y2-y1);
b1 = -((w2-w1)*(y3-y1)-(w3-w1)*(y2-y1))/2.0;
a2 = -(z2-z1)*x3+(z3-z1)*x2;
b2 = ((w2-w1)*x3 - (w3-w1)*x2)/2.0;
a = a1*a1 + a2*a2 + dnm*dnm;
b = 2*(a1*b1 + a2*(b2-y1*dnm) - z1*dnm*dnm);
c = (b2-y1*dnm)*(b2-y1*dnm) + b1*b1 + dnm*dnm*(z1*z1 - l*l);

denta = b*b - 4.0*a*c;
z0 = -0.5*(b-sqrt(denta))/a;
x0 = (a1*z0 + b1)/dnm;
y0 = (a2*z0 + b2)/dnm;
   
set(handles.edit4,'string',num2str(x0));
set(handles.edit5,'string',num2str(y0));
set(handles.edit6,'string',num2str(z0));
% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)

ModelName = 'AssemRobot_Matlab';
global var;

%theta1
theta1= get(handles.slider1,'value');
set(handles.edit1,'string',num2str(theta1));

%theta2
theta2= get(handles.slider2,'value');
set(handles.edit2,'string',num2str(theta2));

%theta3
theta3= get(handles.slider3,'value');
set(handles.edit3,'string',num2str(theta3));

%////////////////////////////////////////////////////////////
set_param([ModelName '/Gain'],'Gain',num2str(theta1));
set_param([ModelName '/Gain1'],'Gain',num2str(theta2));
set_param([ModelName '/Gain2'],'Gain',num2str(theta3));

%Forward Kinematics

L = 150;
l = 344;
d = 40;
wb = 112;
wp = 60;
a = wp - wb; % -52
b = -sqrt(3)/2*a;
c = -0.5*a;

x1 = 0
x2 = -(sqrt(3)/2*L*cosd(theta2) + b)
x3 = (sqrt(3)/2*L*cosd(theta3) + b)

y1 = (L*cosd(theta1) - a)
y2 = -(0.5*L*cosd(theta2) + c)
y3 = -(0.5*L*cosd(theta3) + c)

z1 = L*sind(theta1) + d
z2 = L*sind(theta2) + d
z3 = L*sind(theta3) + d

dnm = (y2-y1)*x3-(y3-y1)*x2;
 
w1 = y1*y1 + z1*z1;
w2 = x2*x2 + y2*y2 + z2*z2;
w3 = x3*x3 + y3*y3 + z3*z3;

a1 = (z2-z1)*(y3-y1)-(z3-z1)*(y2-y1);
b1 = -((w2-w1)*(y3-y1)-(w3-w1)*(y2-y1))/2.0;
a2 = -(z2-z1)*x3+(z3-z1)*x2;
b2 = ((w2-w1)*x3 - (w3-w1)*x2)/2.0;
a = a1*a1 + a2*a2 + dnm*dnm;
b = 2*(a1*b1 + a2*(b2-y1*dnm) - z1*dnm*dnm);
c = (b2-y1*dnm)*(b2-y1*dnm) + b1*b1 + dnm*dnm*(z1*z1 - l*l);

denta = b*b - 4.0*a*c;
z0 = -0.5*(b-sqrt(denta))/a;
x0 = (a1*z0 + b1)/dnm;
y0 = (a2*z0 + b2)/dnm;
   
set(handles.edit4,'string',num2str(x0));
set(handles.edit5,'string',num2str(y0));
set(handles.edit6,'string',num2str(z0));
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

function slider2_CreateFcn(hObject, eventdata, handles)
%--------------------------------------------------------------------
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


function slider3_Callback(hObject, eventdata, handles)
ModelName = 'AssemRobot_Matlab';
global var;

%theta1
theta1= get(handles.slider1,'value');
set(handles.edit1,'string',num2str(theta1));

%theta2
theta2= get(handles.slider2,'value');
set(handles.edit2,'string',num2str(theta2));

%theta3
theta3= get(handles.slider3,'value');
set(handles.edit3,'string',num2str(theta3));

%////////////////////////////////////////////////////////////
set_param([ModelName '/Gain'],'Gain',num2str(theta1));
set_param([ModelName '/Gain1'],'Gain',num2str(theta2));
set_param([ModelName '/Gain2'],'Gain',num2str(theta3));

%Forward Kinematics

L = 150;
l = 344;
d = 40;
wb = 112;
wp = 60;
a = wp - wb; % -52
b = -sqrt(3)/2*a;
c = -0.5*a;

x1 = 0
x2 = -(sqrt(3)/2*L*cosd(theta2) + b)
x3 = (sqrt(3)/2*L*cosd(theta3) + b)

y1 = (L*cosd(theta1) - a)
y2 = -(0.5*L*cosd(theta2) + c)
y3 = -(0.5*L*cosd(theta3) + c)

z1 = L*sind(theta1) + d
z2 = L*sind(theta2) + d
z3 = L*sind(theta3) + d

dnm = (y2-y1)*x3-(y3-y1)*x2;
 
w1 = y1*y1 + z1*z1;
w2 = x2*x2 + y2*y2 + z2*z2;
w3 = x3*x3 + y3*y3 + z3*z3;

a1 = (z2-z1)*(y3-y1)-(z3-z1)*(y2-y1);
b1 = -((w2-w1)*(y3-y1)-(w3-w1)*(y2-y1))/2.0;
a2 = -(z2-z1)*x3+(z3-z1)*x2;
b2 = ((w2-w1)*x3 - (w3-w1)*x2)/2.0;
a = a1*a1 + a2*a2 + dnm*dnm;
b = 2*(a1*b1 + a2*(b2-y1*dnm) - z1*dnm*dnm);
c = (b2-y1*dnm)*(b2-y1*dnm) + b1*b1 + dnm*dnm*(z1*z1 - l*l);

denta = b*b - 4.0*a*c;
z0 = -0.5*(b-sqrt(denta))/a;
x0 = (a1*z0 + b1)/dnm;
y0 = (a2*z0 + b2)/dnm;
   
set(handles.edit4,'string',num2str(x0));
set(handles.edit5,'string',num2str(y0));
set(handles.edit6,'string',num2str(z0));
    
% --- Executes during object creation, after setting all properties.
function slider3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)



% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
choice = questdlg('Would you like to close?', ...
        'Menu', ...
        'Yes','No','Yes');
switch choice
    case 'Yes'
        close
    case 'No'
end   


function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double


% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit6_Callback(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit6 as text
%        str2double(get(hObject,'String')) returns contents of edit6 as a double


% --- Executes during object creation, after setting all properties.
function edit6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit7_Callback(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit7 as text
%        str2double(get(hObject,'String')) returns contents of edit7 as a double


% --- Executes during object creation, after setting all properties.
function edit7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit8_Callback(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit8 as text
%        str2double(get(hObject,'String')) returns contents of edit8 as a double


% --- Executes during object creation, after setting all properties.
function edit8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit9_Callback(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit9 as text
%        str2double(get(hObject,'String')) returns contents of edit9 as a double


% --- Executes during object creation, after setting all properties.
function edit9_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
ModelName = 'AssemRobot_Matlab';
global var;

L = 150;
l = 344;
d = 40;
wb = 112;
wp = 60;
a = wp - wb; % -52
b = -sqrt(3)/2*a;
c = -0.5*a;

x = str2double(get(handles.edit4,'string'));
y = str2double(get(handles.edit5,'string'));
z = str2double(get(handles.edit6,'string'));

E1 = -2*L*(y + a);
F1 = -2*L*(z - d);
G1 = x*x + y*y + z*z + a*a + d*d + 2*y*a - 2*z*d + L*L -l*l;

E2 = L*(sqrt(3)*(x + b) + y + c);
F2 = -2*L*(z - d);
G2 = x*x + y*y + z*z + b*b +c*c + d*d + 2*b*x + 2*c*y -2*z*d + L*L - l*l;

E3 = L*(sqrt(3)*(-x + b) + y + c);
F3 = -2*L*(z - d);
G3 = x*x + y*y + z*z + b*b +c*c + d*d - 2*b*x + 2*c*y -2*z*d + L*L - l*l;

t1 =  (-F1 - sqrt(E1*E1 + F1*F1 - G1*G1))/(G1 - E1);
t2 =  (-F2 - sqrt(E2*E2 + F2*F2 - G2*G2))/(G2 - E2);
t3 =  (-F3 - sqrt(E3*E3 + F3*F3 - G3*G3))/(G3 - E3);

x11 = round(2*atan(t1)*180/pi,1);
y11 = round(2*atan(t2)*180/pi,1);
z11 = round(2*atan(t3)*180/pi,1);

if x11 < exp(-5) x11 = 0; end
if y11 < exp(-5) y11 = 0; end
if z11 < exp(-5) z11 = 0; end

set(handles.edit7,'string',num2str(x11));
set(handles.edit8,'string',num2str(y11));
set(handles.edit9,'string',num2str(z11));



% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
ModelName = 'AssemRobot_Matlab';
global var;
%--------------------------------------------------------------------------
    theta1=str2double(get(handles.edit7,'string'))
    theta2=str2double(get(handles.edit8,'string'))
    theta3=str2double(get(handles.edit9,'string'))

%--------------------------------------------------------------------------
set_param([ModelName '/Gain'],'Gain',num2str(theta1));
set_param([ModelName '/Gain1'],'Gain',num2str(theta2));
set_param([ModelName '/Gain2'],'Gain',num2str(theta3));
%--------------------------------------------------------------------------
    set(handles.edit1,'string',num2str(theta1));
    set(handles.edit2,'string',num2str(theta2));
    set(handles.edit3,'string',num2str(theta3));
%--------------------------------------------------------------------------
    set(handles.slider1,'value',theta1);
    set(handles.slider2,'value',theta2);
    set(handles.slider3,'value',theta3);

% --- Executes on slider movement.


function edit1_Callback(hObject, eventdata, handles)

% --- Executes during object creation, after setting all properties.

function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit2_Callback(hObject, eventdata, handles)


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit3_Callback(hObject, eventdata, handles)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton11.
function pushbutton11_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
ModelName = 'AssemRobot_Matlab';
%open_system(ModelName);
%clear all;
simOut = sim(ModelName);
