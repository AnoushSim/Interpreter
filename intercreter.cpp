#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include <cstring>
#include <sstream>
#include <ctype.h>


std::string getType(std::string str) {
        if(str[0] == '"' ) {
                return "string";
        }
        else {
        	    int count = 0;
                for(int ix = 0; ix < str.size() ; ++ix) {
                        if(str[ix] == '.')
                            count += 1;
                    }           
                      if (count == 1 && str[str.size()] != '.')
                         return "double";
                      else if(count > 1)
                         return "Error!No such type!";
                }
         
        return "int";
}


int main(int argc, char *argv[])
{
	std::map<std::string , std::pair <std::string , std::string> > mymap;
	std::map<std::string , std::pair <std::string , std::string> >::iterator it;
    const int m = 20;
    std::ifstream inFile;
    if (argc < 2) {
    	std::cout << " There is no file name to read!" << std::endl;
    	return -1;
	}
	std::string  _fname(argv[1]);
	std::string key (".pgh");
    std::size_t found = _fname.rfind(key);
    if (found !=  _fname.length() - 4)  {
		std::cout << "Not correct file format!" << std::endl;
		return -1;
	}
    inFile.open(argv[1]);
        if (inFile.fail())
        {
            std::cerr << "FileError" << argv[1] << "' could not be found" << std::endl;
        }
        else {
            std::string* line = new std::string[m];
            int i = 0;
            while (std::getline(inFile, line[i]))
            {
                std::cout << "line " << i + 1 << ": " << line[i] << std::endl;
                ++i;
            }
            for (int index = 0; index < i; ++index) {
          const int n = 10;
          int ix = 0;
	       std::string* str = new std::string[n];
          std::istringstream iss(line[index]);
          while (!iss.eof())
    {
        std::string subs;
        iss >> subs;
        str[ix] = subs;
		    std::cout << "Substring: " << str[ix++] << std::endl;
    } 
    
    if (str[ix - 1] != ";" ) {
	     
		     std::cout << "ERROR! Line must end with ';'." << std::endl;
         return -1;
    }
	
	if(str[0] == "pghvar") {
		
		std::string name = str[1];
		if (isdigit(name[0])) {
			std::cout << "Error! Variable name can't begin with number!" <<std::endl;
			return -1;
		}
	
    	if (str[2] == "=") {
    		
    		if (str[4] == "+" || str[4] == "-" || str[4] == "*" || str[4] == "/"  ) { 
    		   std::string ftype = getType(str[3]);
    		   if (ftype == "int") {
    		  		int val1, val2,  _inttmpop;
    		  		val1 = std::stoi(str[3]);
    		  		val2 = std::stoi(str[5]);
    		  		if (str[4] == "+") {
    		  			_inttmpop = val1 + val2;
    		  			std::string sresult = std::to_string( _inttmpop );
    		  			mymap[str[1]] = std::make_pair(sresult,"int");
    		  		
					  } 
					  else if ( str[4] == "-") {
    		  			_inttmpop = val1 - val2;
    		  			std::string sresult = std::to_string( _inttmpop );
    		  			mymap[str[1]] = std::make_pair(sresult,"int");
					  } 
					else if ( str[4] == "*") {
    		  			_inttmpop = val1 * val2;
    		  			std::string sresult = std::to_string( _inttmpop );
    		  			mymap[str[1]] = std::make_pair(sresult,"int");
					  } 
					else if ( str[4] == "/") {
    		  			_inttmpop = val1 / val2;
    		  			std::string sresult = std::to_string( _inttmpop );
    		  			mymap[str[1]] = std::make_pair(sresult,"int");
					  } 
    		  			
				  }
				 if (ftype == "double") {
    		  		double val1,val2, _doubtmpop;
    		  		val1 = std::stod(str[3]);
    		  		val2 = std::stod(str[5]);
    		  		if (str[4] == "+") {
    		  			_doubtmpop = val1 + val2;
    		  			std::string sresult = std::to_string( _doubtmpop );
    		  			mymap[str[1]] = std::make_pair(sresult,"double");
					  } 
					else if ( str[4] == "-") {
    		  			_doubtmpop = val1 - val2;
    		  			std::string sresult = std::to_string( _doubtmpop );
    		  			mymap[str[1]] = std::make_pair(sresult,"double");
					  } 
					else if ( str[4] == "*") {
    		  			_doubtmpop = val1 * val2;
    		  			std::string sresult = std::to_string( _doubtmpop );
    		  			mymap[str[1]] = std::make_pair(sresult,"double");
					  } 
					else if ( str[4] == "/") {
    		  			_doubtmpop = val1 / val2;
    		  			std::string sresult = std::to_string( _doubtmpop );
    		  			mymap[str[1]] = std::make_pair(sresult,"double");
					  } 
    		  			
				  }
				if (ftype == "string") {
    		  		std::string  _strtmpop;
    		  		if (str[4] == "+") {
    		  			_strtmpop = str[3] + str[5];
    		  			mymap[str[1]] = std::make_pair(_strtmpop,"string");
    		  		
					  } 
					else if ( str[4] == "-" || str[4] == "*" || str[4] == "/") 
					      std::cout << "Undefined operations with string objects!";
    		  			
				  }
			  }
			
			}
    	std::string _type = getType(str[3]);
			if (_type == "int") 
			   mymap[str[1]] = std::make_pair(str[3],"int");
			if (_type == "double") 
			   mymap[str[1]] = std::make_pair(str[3],"double");
			if (_type == "string") 
			   mymap[str[1]] = std::make_pair(str[3],"string");
		}
		
	if (str[0] == "print") {
	  
	  if (str[2] == ";") {
	    it = mymap.find(str[1]);
      if (it == mymap.end()) {
        std::cout << "There is no such a variable! ";
        return -1;
      }
      else {
        std::cout << mymap[str[1]].first;
      }
	  }
	  
	  
	  if (str[2] == "=") {
	    if (str[4] == ";") {
	      it = mymap.find(str[1]);
        if (it == mymap.end()) {
        std::cout << "There is no such a variable! ";
        return -1;
      }
      else {
        std::string operandtype = getType(str[3]);
        if (operandtype == mymap[str[1]].second) {
          mymap[str[1]].first = str[3];
          std::cout << mymap[str[1]].first;
        }
        else {
          mymap[str[1]].second = operandtype;
          mymap[str[1]].first = str[3];
          std::cout << mymap[str[1]].first;
        }
       }
	    }
	    
	    if (str[4] == "+" || str[4] == "-" || str[4] == "*" || str[4] == "/") {
	      it = mymap.find(str[1]);
        if (it == mymap.end()) {
        std::cout << "There is no such a variable! ";
        return -1;
      }
      else {
	      std::string types = getType(str[3]);
	      mymap[str[1]].second = types; 
	        if (types == "int") {
    		  		int val1, val2,  _inttmpop;
    		  		val1 = std::stoi(str[3]);
    		  		val2 = std::stoi(str[5]);
    		  		if (str[4] == "+") {
    		  			_inttmpop = val1 + val2;
    		  			std::string sresult = std::to_string( _inttmpop );
    		  			mymap[str[1]].first = sresult;
    		  			std::cout << mymap[str[1]].first;
    		  		
					  } 
					  else if ( str[4] == "-") {
    		  			_inttmpop = val1 - val2;
    		  			std::string sresult = std::to_string( _inttmpop );
    		  		  mymap[str[1]].first = sresult;
    		  			std::cout << mymap[str[1]].first;
					  } 
					else if ( str[4] == "*") {
    		  			_inttmpop = val1 * val2;
    		  			std::string sresult = std::to_string( _inttmpop );
    		  			mymap[str[1]].first = sresult;
    		  			std::cout << mymap[str[1]].first;
					  } 
					else if ( str[4] == "/") {
    		  			_inttmpop = val1 / val2;
    		  			std::string sresult = std::to_string( _inttmpop );
    		  			mymap[str[1]].first = sresult;
    		  			std::cout << mymap[str[1]].first;
					  } 
    		  			
				  }
				 if (types == "double") {
    		  		double val1,val2, _doubtmpop;
    		  		val1 = std::stod(str[3]);
    		  		val2 = std::stod(str[5]);
    		  		if (str[4] == "+") {
    		  			_doubtmpop = val1 + val2;
    		  			std::string sresult = std::to_string( _doubtmpop );
    		  			mymap[str[1]].first = sresult;
    		  			std::cout << mymap[str[1]].first;
					  } 
					else if ( str[4] == "-") {
    		  			_doubtmpop = val1 - val2;
    		  			std::string sresult = std::to_string( _doubtmpop );
    		  			mymap[str[1]].first = sresult;
    		  			std::cout << mymap[str[1]].first;
					  } 
					else if ( str[4] == "*") {
    		  			_doubtmpop = val1 * val2;
    		  			std::string sresult = std::to_string( _doubtmpop );
    		  			mymap[str[1]].first = sresult;
    		  			std::cout << mymap[str[1]].first;
					  } 
					else if ( str[4] == "/") {
    		  			_doubtmpop = val1 / val2;
    		  			std::string sresult = std::to_string( _doubtmpop );
    		  			mymap[str[1]].first = sresult;
    		  			std::cout << mymap[str[1]].first;
					  } 
    		  			
				  }
				if (types == "string") {
    		  		std::string  _strtmpop;
    		  		if (str[4] == "+") {
    		  			_strtmpop = str[3] + str[5];
    		  			mymap[str[1]].first = _strtmpop;
    		  			std::cout << mymap[str[1]].first;
    		  		
					  } 
				  	else if ( str[4] == "-" || str[4] == "*" || str[4] == "/") 
					      std::cout << "Undefined operations with string objects!";
    		  			
				  }
	      }
       }
	    }
	    
	    if (str[2] == "+" || str[2] == "-" || str[2] == "*" || str[2] == "/" ) {
	      it = mymap.find(str[1]);
	      std::string var_type = getType(str[1]);
	      if (it != mymap.end() ) {
	        std::string ftype = mymap[str[1]].second;
	        std::string ltype = getType(str[3]);
	        if (ftype == ltype) {
	          if(ftype == "int") {
	            if(str[2] == "+") {
	            int x = std::stoi(mymap[str[1]].first);
	            x += std::stoi(str[3]);
	            std::cout << x;
	            }
	            if(str[2] == "-") {
	            int x = std::stoi(mymap[str[1]].first);
	            x -= std::stoi(str[3]);
	            std::cout << x;
	            }
	            if(str[2] == "*") {
	            int x = std::stoi(mymap[str[1]].first);
	            x *= std::stoi(str[3]);
	            std::cout << x;
	            }
	            if(str[2] == "/") {
	            int x = std::stoi(mymap[str[1]].first);
	            x /= std::stoi(str[3]);
	            std::cout << x;
	            }
	          }
	          if(ftype == "double") {
	            if(str[2] == "+") {
	            double x = std::stod(mymap[str[1]].first);
	            x += std::stod(str[3]);
	            std::cout << x;
	            }
	            if(str[2] == "-") {
	            double x = std::stod(mymap[str[1]].first);
	            x -= std::stod(str[3]);
	            std::cout << x;
	            }
	            if(str[2] == "*") {
	            double x = std::stod(mymap[str[1]].first);
	            x *= std::stod(str[3]);
	            std::cout << x;
	            }
	            if(str[2] == "/") {
	            double x = std::stod(mymap[str[1]].first);
	            x /= std::stod(str[3]);
	            std::cout << x;
	            }
	          }
	          if(ftype == "string") {
	            if(str[2] == "+") {
	            std::string  x = mymap[str[1]].first;
	            x += str[3];
	            std::cout << x;
	            }
	            if(str[2] == "-" || str[2] == "*" || str[2] == "/") 
	                 std::cout << "Undefined operations with string objects!"<< std::endl;
	            
	          }
	        }
	        else {
	          
	        } }
	       
	       else if (it == mymap.end() && (var_type == "int" || var_type == "double")) {
	        std::string _var_type = getType(str[3]);
	        if(_var_type == var_type) {
	          if(var_type == "int") {
	            int tmp = std::stoi(str[1]);
	            if(str[2] == "+") 
	              tmp += std::stoi(str[3]);
	            else if(str[2] == "-")
	              tmp -= std::stoi(str[3]);
	            else if(str[2] == "*")
	              tmp *= std::stoi(str[3]);
	            else if(str[2] == "/")
	              tmp /= std::stoi(str[3]);
	            std::cout << tmp <<std::endl;
	          }
	          if(var_type == "double") {
	            int tmp = std::stod(str[1]);
	            if(str[2] == "+") 
	              tmp += std::stod(str[3]);
	            else if(str[2] == "-")
	              tmp -= std::stod(str[3]);
	            else if(str[2] == "*")
	              tmp *= std::stod(str[3]);
	            else if(str[2] == "/")
	              tmp /= std::stod(str[3]);
	            std::cout << tmp <<std::endl;
	          }
	        }
	         else {
	           std::string ftype = mymap[str[1]].second;
	          if (ftype == "int") {
	            std::string ltype = getType(str[3]);
	            if (ltype == "double") {
	              if(str[2] == "+") {
	              double x = std::stod(str[3]);
	              int y = static_cast<int>(x);
	              y += std::stoi(mymap[str[1]].first);
	              std::cout << y;
	              }
	              if(str[2] == "*") {
	              double x = std::stod(str[3]);
	              int y = static_cast<int>(x);
	              y *= std::stoi(mymap[str[1]].first);
	              std::cout << y;
	              }
	              if(str[2] == "-") {
	              double x = std::stod(str[3]);
	              int y = static_cast<int>(x);
	              y -= std::stoi(mymap[str[1]].first);
	              std::cout << y;
	              }
	              if(str[2] == "/") {
	              double x = std::stod(str[3]);
	              int y = static_cast<int>(x);
	              y /= std::stoi(mymap[str[1]].first);
	              std::cout << y;
	              }
	            }
	            if (ltype == "string") {
	              std::cout << "Undefined operation!";
	              return -1;
	            }
	          }
	          if (ftype == "double") {
	            std::string ltype = getType(str[3]);
	            if (ltype == "int") {
	              if(str[2] == "+") {
	              int x = std::stoi(str[3]);
	              double y = static_cast<double>(x);
	              y += std::stod(mymap[str[1]].first);
	              std::cout << y;
	              }
	              if(str[2] == "*") {
	              int x = std::stoi(str[3]);
	              double y = static_cast<double>(x);
	              y *= std::stod(mymap[str[1]].first);
	              std::cout << y;
	              }
	              if(str[2] == "-") {
	              int x = std::stoi(str[3]);
	              double y = static_cast<double>(x);
	              y -= std::stoi(mymap[str[1]].first);
	              std::cout << y;
	              }
	              if(str[2] == "/") {
	              int x = std::stoi(str[3]);
	              double y = static_cast<double>(x);
	              y /= std::stod(mymap[str[1]].first);
	              std::cout << y;
	              }
	            }
	            if (ltype == "string") {
	              std::cout << "Undefined operation!";
	              return -1;
	            }
	         }
	         if (ftype == "string") {
	           if (str[2] == "+") {
	             std::string x = mymap[str[1]].first + str[3];
	             std::cout << x;
	           }
	           if (str[2] == "*" || str[2] == "-" || str[2] == "/") {
	             std::cout << "Undefined operations";
	             return -1;
	           }
	         }
	         }
	       }
	       else if (it == mymap.end())
	          std::cout << "There is no such a variable!" << std::endl;
	      
	    }
	}
	if (str[0] != "pghvar" || str[0] != "print") {
	  it = mymap.find(str[0]);
	  if (it == mymap.end()) {
	    std::cout << "Incorrect variable name!" << std::endl;
	    return -1;
	  }
	  else {
	    if (str[1] != "=") {
	      std::cout << "Incorrect command line ! "<<std::endl;
	      return -1;
	    }
	    else {
	      if (str[3] == "+" || str[3] == "-" || str[3] == "*" || str[3] == "/" ) {
	        it = mymap.find(str[2]);
	        if(it != mymap.end()) {
	          std::string ltype = getType(str[4]);
	          if (ltype == mymap[str[2]].second) {
	            if (str[3] == "+") {
	              if (ltype == "int") {
	                int tmp = std::stoi(mymap[str[2]].first);
	                tmp += std::stoi(str[4]);
	                std::string sresult = std::to_string( tmp );
	                mymap[str[0]].first = sresult;
	              }
	              if (ltype == "double") {
	                double tmp = std::stod(mymap[str[2]].first);
	                tmp += std::stod(str[4]);
	                std::string sresult = std::to_string( tmp );
	                mymap[str[0]].first = sresult;
	              }
	              if (ltype == "string") {
	                std::string tmp = mymap[str[2]].first;
	                tmp += str[4];
	                std::string sresult = tmp;
	                mymap[str[0]].first = sresult;
	              }
	            }
	             if (str[3] == "-") {
	              if (ltype == "int") {
	                int tmp = std::stoi(mymap[str[2]].first);
	                tmp -= std::stoi(str[4]);
	                std::string sresult = std::to_string( tmp );
	                mymap[str[0]].first = sresult;
	              }
	              if (ltype == "double") {
	                double tmp = std::stod(mymap[str[2]].first);
	                tmp -= std::stod(str[4]);
	                std::string sresult = std::to_string( tmp );
	                mymap[str[0]].first = sresult;
	              }
	              if (ltype == "string") {
	                std::cout << "undefined operation with string objects!";
	                return -1;
	              }
	            } 
	            if (str[3] == "*") {
	              if (ltype == "int") {
	                int tmp = std::stoi(mymap[str[2]].first);
	                tmp *= std::stoi(str[4]);
	                std::string sresult = std::to_string( tmp );
	                mymap[str[0]].first = sresult;
	              }
	              if (ltype == "double") {
	                double tmp = std::stod(mymap[str[2]].first);
	                tmp *= std::stod(str[4]);
	                std::string sresult = std::to_string( tmp );
	                mymap[str[0]].first = sresult;
	              }
	              if (ltype == "string") {
	                std::cout << "undefined operation with string objects!";
	                return -1;
	              }
	            } 
	            if (str[3] == "/") {
	              if (ltype == "int") {
	                int tmp = std::stoi(mymap[str[2]].first);
	                tmp /= std::stoi(str[4]);
	                std::string sresult = std::to_string( tmp );
	                mymap[str[0]].first = sresult;
	              }
	              if (ltype == "double") {
	                double tmp = std::stod(mymap[str[2]].first);
	                tmp /= std::stod(str[4]);
	                std::string sresult = std::to_string( tmp );
	                mymap[str[0]].first = sresult;
	              }
	              if (ltype == "string") {
	                std::cout << "undefined operation with string objects!";
	                return -1;
	              }
	            }
	          }
	          else {
	            std::string ftype = mymap[str[2]].second;
	          if (ftype == "int") {
	            if (ltype == "double") {
	              if(str[3] == "+") {
	              double x = std::stod(str[4]);
	              int y = static_cast<int>(x);
	              y += std::stoi(mymap[str[2]].first);
	              std::string sresult = std::to_string( y );
	              mymap[str[0]].first = sresult;
	              }
	              if(str[3] == "*") {
	              double x = std::stod(str[4]);
	              int y = static_cast<int>(x);
	              y *= std::stoi(mymap[str[2]].first);
	              std::string sresult = std::to_string( y );
	              mymap[str[0]].first = sresult;
	              }
	              if(str[3] == "-") {
	              double x = std::stod(str[4]);
	              int y = static_cast<int>(x);
	              y -= std::stoi(mymap[str[2]].first);
	              std::cout << y;
	              }
	              if(str[3] == "/") {
	              double x = std::stod(str[4]);
	              int y = static_cast<int>(x);
	              y /= std::stoi(mymap[str[2]].first);
	              std::string sresult = std::to_string( y );
	              mymap[str[0]].first = sresult;
	              }
	            }
	            if (ltype == "string") {
	              std::cout << "Undefined operation!";
	              return -1;
	            }
	          }
	          if (ftype == "double") {
	            if (ltype == "int") {
	              if(str[3] == "+") {
	              int x = std::stoi(str[4]);
	              double y = static_cast<double>(x);
	              y += std::stod(mymap[str[2]].first);
	              std::string sresult = std::to_string( y );
	              mymap[str[0]].first = sresult;
	              }
	              if(str[3] == "*") {
	              int x = std::stoi(str[4]);
	              double y = static_cast<double>(x);
	              y *= std::stod(mymap[str[2]].first);
	              std::string sresult = std::to_string( y );
	              mymap[str[0]].first = sresult;
	              }
	              if(str[3] == "-") {
	              int x = std::stoi(str[4]);
	              double y = static_cast<double>(x);
	              y -= std::stoi(mymap[str[2]].first);
	              std::string sresult = std::to_string( y );
	              mymap[str[0]].first = sresult;
	              }
	              if(str[3] == "/") {
	              int x = std::stoi(str[4]);
	              double y = static_cast<double>(x);
	              y /= std::stod(mymap[str[2]].first);
	              std::string sresult = std::to_string( y );
	              mymap[str[0]].first = sresult;
	              }
	            }
	            if (ltype == "string") {
	              std::cout << "Undefined operation!";
	              return -1;
	            }
	         }
	         if (ftype == "string") {
	           if (str[3] == "+") {
	             std::string x = mymap[str[2]].first + str[4];
	             std::cout << x;
	           }
	           if (str[3] == "*" || str[3] == "-" || str[3] == "/") {
	             std::cout << "Undefined operations";
	             return -1;
	           }
	         }
	        }
	          
	        }
	      }
	    
	    else {
	      it = mymap.find(str[2]);
	      if (it != mymap.end()) {
	        mymap[str[0]].first = mymap[str[2]].first;
	        mymap[str[0]].second = mymap[str[2]].second;
	      }
	      else {
	        std::string typ = getType(str[2]);
	        std::string ltyp = mymap[str[0]].second;
	        if (typ != ltyp) {
	          mymap[str[0]].first = str[2];
	          mymap[str[0]].second = ltyp;
	        }
	        else 
	           mymap[str[0]].first = str[2];
	      }
	    }
	   }
	  }
	}
}
        }
        

        return 0;
	 }  

