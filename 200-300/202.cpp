const int dx=200, dy=20; //canvas offset
const double mag=1000;   //size of mirrors in pixels
const double cos30=sqrt(3.0)/2.0; //handy constant
const double pi=3.1415926535897932384626433; //no life without pi

//return fractional part of real number
double fraction(double x)
{
int ix=(int)x;
return(x-ix);
}

//draw line to location on mirror:
// int(d)%3 = mirror;  fraction(d)=location on mirror
void linetomirrorpoint(double d)
{
int mirror;
int x,y;
double mirrf;

mirrf=fraction(d);  //fractional part of d
mirror=(int)d;      //integer part of d
mirror%=3;          //mirror number: 0=AB, 1=BC, 2=CA
if(mirror==0){      //AB
  x=dx+(int)(mag*mirrf+0.5);
  y=dy;
  }
else if(mirror==1){ //BC
  x=dx+(int)(mag*(1.0-0.5*mirrf)+0.5);
  y=dy+(int)(mag*mirrf*cos30+0.5);
  }
else{  //CA
  x=dx+(int)(mag*(0.5-0.5*mirrf)+0.5);
  y=dy+(int)(mag*(1-mirrf)*cos30+0.5);
  }
lto(x,y);
}

//main function:
//setup mirror, calculates hit locations
void prob202draw(void)
{
const double ey=7.0,ex=3.0; //exit coordinates C' (nbounces = 2*ey-3)
double dmir;                //target location on mirror
double fdmir;               //fractional part of dmir
int idmir;                  //integer part of dmir
double switchpoint;
int i;
double alpha;               //laser angle

//draw mirrors:
pcol(clBlack);      //set pen colour to black
mto(dx,dy);         //move to canvas coordinate
lto(dx+mag, dy);    //draw line to next coordinate
lto(dx+mag/2, dy+(int)(mag*cos30+0.5));
lto(dx,dy);

//move to laser start location: entrance C:
mto(dx+(int)(0.5*mag+0.5),dy+(int)(cos30*mag+0.5));
pcol(clRed);      //set pen colour to red

//calculate mirror points:
for(i=1;i<=ey;i++){
  //calculate horizontal intersections:
  if(i%2==1)
    dmir=0.5+(double)i*ex/(2.0*ey);
  else
    dmir=2.0+(double)i*ex/(2.0*ey);
  linetomirrorpoint(dmir);

  //calculate diagonal intersections:
  if(i<ey){
    idmir=(int)dmir;
    fdmir=fraction(dmir);
    switchpoint=0.5-0.5*ex/(cos30*ey);
    alpha=atan(2*ey*cos30/ex);
    if(fdmir<switchpoint)
      dmir=(double)idmir+2.0+1.0-fdmir*sin(alpha)/(sin(alpha-pi/3));
    else
      dmir=(double)idmir+1.0+(1.0-fdmir)*sin(alpha)/(sin(2*pi/3-alpha));
    linetomirrorpoint(dmir);
    }
  }
}