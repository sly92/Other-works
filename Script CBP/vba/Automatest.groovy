def groovyUtils = new com.eviware.soapui.support.GroovyUtils(context)

// Initialisation des variables
def text = "~"
def n=0
def j=0
def defaut = false
//def ajout = false


def csvFilePath = "[chemin du csv]"

def AssertionList = new ArrayList();
def libelleKO = new ArrayList();
def categorie = new ArrayList();
def testsMultiple = new ArrayList();

// Lecture du fichier csv
context.fileReader = new BufferedReader(new FileReader(csvFilePath))
rowsData = context.fileReader.readLines()
int rowsize = rowsData.size()

// Ecriture du contenu dans un tableaux
for(int i = 1;  i &lt; rowsize;  i++)
{

    rowdata = rowsData[i]
    String[] data = rowdata.split(";")
    //log.info data[2]
    libelleKO.add(data[2])
     if(!categorie.contains(data[0])){
      categorie.add(data[0])
      log.info(data[0])
     }
     testsMultiple.add(data[3])
   
}


def testSuiteList = project.getTestSuiteList()

//Parcours des suite de tests 
testSuiteList.each
{

//log.info it.name


testSuite = project.getTestSuiteByName(it.name)

def paquet=''
def token=''

     if(it.name!="") {
            paquet = 'Contrôle de '+ categorie[j]
            //log.info(paquet)
            //log.info(categorie[0])
           //Garde le même index du tableau pour tout le paquet -> pas d'incrementation dans le paquet
            defaut=testsMultiple[j].toBoolean()
            //log.info(defaut)
     }


testCaseList = testSuite.getTestCaseList()
log.info " ${text*5} Parcours des requetes du paquet : $testSuite.name..."

//Parcours des cas de tests 
testCaseList.each
{


testCase = testSuite.getTestCaseByName(it.name)
testCase.setFailOnError(false)
log.info " ${text*10} Parcours du cas de test :: $testCase.name... "
wsdlTestSteps = testCase.getTestStepsOfType( com.eviware.soapui.impl.wsdl.teststeps.WsdlTestRequestStep.class )

//Parcours des requêtes
wsdlTestSteps.each
{

assertionList = it.getAssertionList()

for (assertion in assertionList)
{
	it.removeAssertion(assertion)
	log.info "${text*5} Suppression de l'assertion :: ${it.toString()}"
}

def assertion = it.getAssertionByName(paquet)

def soap = it.addAssertion("SOAP Response")
def contains = it.addAssertion("Contains")
contains.name = paquet
token = libelleKO[n]
contains.setToken(token)
contains.setIgnoreCase(true)
}
//Passage à la ligne suivante dans le csv (cas de tests qui n'utilise pas une valeurs par defaut)
if(!defaut)
n=n+1
}
if(defaut)
n=n+1
j=j+1	
}

