//Molecular Mass Calculator

function getMass(str){
    if(str == "H"){
        return 1.008;
    } else if(str == "He"){
        return 4.003;
    } else if(str == "Li"){
        return 6.94;
    } else if(str == "Be"){
        return 9.012;
    } else if(str == "B"){
        return 10.81;
    } else if(str == "C"){
        return 12.011;
    } else if(str == "N"){
        return 14.007;
    } else if(str == "O"){
        return 15.999;
    } else if(str == "F"){
        return 18.998;
    } else if(str == "Ne"){
        return 20.18;
    } else if(str == "Na"){
        return 22.990;
    } else if(str == "Mg"){
        return 24.305;
    } else if(str == "Al"){
        return 26.982;
    } else if(str == "Si"){
        return 28.085;
    } else if(str == "Ca"){
        return 40.078;
    } else if(str == "P"){
        return 30.974;
    } else if(str == "S"){
        return 32.06;
    } else if(str == "Cl"){
        return 35.45;
    } else if(str == "Ar"){
        return 39.948;
    } else if(str == "K"){
        return 39.098;
    } else if(str == "Sc"){
        return 44.956;
    } else if(str == "Ti"){
        return 47.867;
    } else if(str == "U"){
        return 238.02891;
    }
}   
    


function run(chem){
    var currentStr = "";
        var currentAmount = "";
        var amount = 1;
        var N = 0;
        console.log(chem.str.length);
        for (var i = 0; i < chem.str.length; i++) {
            //console.log("Scanning: " + chem.str[i]);
            if (isUpper(chem.str[i])) {
                chem.elements++;
            }
            if (chem.str[i] == '(') {
                N++;
            } else if (chem.str[i] == ')') {
                N--;
            }
            if (N === 0) {
                if (currentStr === "") {
                    if (i != chem.str.length - 1 && isLower(chem.str[i + 1])) {
                        currentStr += chem.str[i];
                        currentStr += chem.str[i + 1];
                        //console.log("yeah");
                        i += 1;
                    } else {
                        currentStr += chem.str[i];
                    }

                }
                i++;
                while (isDigit(chem.str[i])) {
                    currentAmount += chem.str[i];
                    i++;
                }
                i--;
                if (currentAmount !== "") {
                    amount = parseInt(currentAmount);
                }
                if (currentStr[0] == '(') {
                    currentStr = currentStr.slice(1);
                }
                var tempChem = {
                        str: currentStr,
                        childN: 0,
                        children: [],
                        elements: 0,
                        amount: amount,
                }
                
                chem.children[chem.childN] = tempChem;
                chem.childN++;
               
                //console.log("Making new child from " + chem.str + ", child: " + tempChem.str);
                currentStr = "";
                currentAmount = "";
                amount = 1;
            } else {
                currentStr += chem.str[i];
            }
            console.log(i);
        }

        //console.log("Outta here " + chem.str);
        if (chem.elements <= 1&& !containsBrackets(chem.str)) {
            console.log(i);
            return;
        } else {
            for (var j = 0; j < chem.childN; j++) {
                run(chem.children[j]);
            }
        }
    }


function calc(chem){
    //console.log("Running calc(" + chem.str + ")");
        var sum = 0;
        if (chem.elements <= 1 && !containsDigit(chem.str) && !containsBrackets(chem.str)) {
            return getMass(chem.str);
        } else {
            for (var i = 0; i < chem.childN; i++) {
                var k = calc(chem.children[i]) * chem.children[i].amount;
                //console.log(chem.children[i].amount + " * " + chem.children[i].str + " = " + k);
                sum += k;
            } 
                
            
            return sum;
        }

}

var chem = { //Chem class
    str: "",
    childN: 0,
    children: [],
    elements: 0,
    amount: 1,
}




function isUpper(str) {
    return (str == str.toUpperCase());
}


function isLower(str) {
    return (str <= 'z' && str >= 'a');
}

function isDigit(str) {
    return /\d/.test(str); //regex
}

function containsDigit(str) {
    for (var i = 0; i < str.length; i++) {
        if (isDigit(str[i])) {
            return true;
        }

    }
    return false;
}

function containsBrackets(str){
    for (var i = 0; i < str.length; i++) {
        if (str[i] == ')' || str[i] == '(') {
            return true;
        }

    }
    return false;

}

function go() {
    var string = $("#input").val();
        chem = { //Chem class
        str: "",
        childN: 0,
        children: [],
        elements: 0,
        amount: 1,
    }
    var newChem = chem;
    //console.log(string);
    newChem.str = string;
    run(newChem);
    var ans = calc(newChem);
    if(ans){
            var tempstr = "$$";
    var isInDigit = false;
    
    for(var i = 0; i < string.length; i++){
        if(isDigit(string[i]) && !isInDigit){
            isInDigit = true;
            tempstr += "_{";

        } else if(isInDigit && !isDigit(string[i])){
            tempstr += "}";
            isInDigit = false;
        } 

        tempstr += string[i];
        
    }
    if(isInDigit){
        tempstr += '}';
    }
    tempstr += "\\approx " + ans + "$$";
    console.log(tempstr);
    $("#ans").append(tempstr);
    MathJax.Hub.Typeset();
    }
    //console.log(ans);
    

}
