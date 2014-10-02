/************************************************************************
  			BlobResult.h
  			
FUNCIONALITAT: Definici� de la classe CBlobResult
AUTOR: Inspecta S.L.
MODIFICACIONS (Modificaci�, Autor, Data):

FUNCTIONALITY: Definition of the CBlobResult class
AUTHOR: Inspecta S.L.
MODIFICATIONS (Modification, Author, Date):

**************************************************************************/


#if !defined(_CLASSE_BLOBRESULT_INCLUDED)
#define _CLASSE_BLOBRESULT_INCLUDED

#if _MSC_VER > 1000 
#pragma once
#endif // _MSC_VER > 1000

#include "BlobLibraryConfiguration.h"
#include "ComponentLabeling.h"
#include "defines.h"
#include <math.h>
#include "opencv/cxcore.h"
#include <opencv2/opencv.hpp>
#include <deque>
#include <limits.h>
#include <stdio.h>
#include <functional>
#include <algorithm>
#include <cfloat>

#include <vector>		// vectors de la STL
#include <functional>
#include "blob.h"
#include "BlobOperators.h"
#include "ComponentLabeling.h"

class CBlobResult  
{
public:

	//Constructor, opencv 1.0 and 2.0 interfaces.
	CBlobResult();
	CBlobResult(IplImage *source, IplImage *mask = NULL, int numThreads=1);
	CBlobResult(cv::Mat &source, const cv::Mat &mask = cv::Mat(),int numThreads=1);
	CBlobResult( const CBlobResult &source );
	//! Destructor
	virtual ~CBlobResult();

	// Function to detect blobs in a new image
	void detect(cv::Mat &source, const cv::Mat &mask = cv::Mat(),int numThreads=1);

	//! operador = per a fer assignacions entre CBlobResult
	//! Assigment operator
	CBlobResult& operator=(const CBlobResult& source);
	//! operador + per concatenar dos CBlobResult
	//! Addition operator to concatenate two sets of blobs
	CBlobResult operator+( const CBlobResult& source ) const;
	
	//! Adds a blob to the set of blobs
	void AddBlob( CBlob *blob );

#ifdef MATRIXCV_ACTIU
	//! Calcula un valor sobre tots els blobs de la classe retornant una MatrixCV
	//! Computes some property on all the blobs of the class
	double_vector GetResult( blobOperator *evaluador ) const;
#endif
	//! Calcula un valor sobre tots els blobs de la classe retornant un std::vector<double>
	//! Computes some property on all the blobs of the class
	double_stl_vector GetSTLResult( blobOperator *evaluador ) const;
	
	//! Calcula un valor sobre un blob de la classe
	//! Computes some property on one blob of the class
	double GetNumber( int indexblob, blobOperator *evaluador ) const;

	//! Retorna aquells blobs que compleixen les condicions del filtre en el destination 
	//! Filters the blobs of the class using some property
	void Filter(CBlobResult &dst,
				int filterAction, blobOperator *evaluador, 
				int condition, double lowLimit, double highLimit = 0 );
	void Filter(CBlobResult &dst,
				int filterAction, blobOperator *evaluador, 
				int condition, double lowLimit, double highLimit = 0 ) const;
	void Filter(CBlobResult &dst,
				FilterAction filterAction, blobOperator *evaluador, 
				FilterCondition condition, double lowLimit, double highLimit = 0 );
			
	//! Retorna l'en�ssim blob segons un determinat criteri
	//! Sorts the blobs of the class acording to some criteria and returns the n-th blob
	void GetNthBlob( blobOperator *criteri, int nBlob, CBlob &dst ) const;
	
	//! Retorna el blob en�ssim
	//! Gets the n-th blob of the class ( without sorting )
	CBlob GetBlob(int indexblob) const;
	CBlob *GetBlob(int indexblob);
	CBlob GetBlobByID(t_labelType id) const;
	CBlob *GetBlobByID(t_labelType id);
	
	//! Elimina tots els blobs de l'objecte
	//! Clears all the blobs of the class
	void ClearBlobs();

	//! Escriu els blobs a un fitxer
	//! Prints some features of all the blobs in a file
	void PrintBlobs( char *nom_fitxer ) const;

	// Returns blob with center nearest to point pt
	CBlob* getBlobNearestTo(cv::Point pt);

//Metodes GET/SET

	//! Retorna el total de blobs
	//! Gets the total number of blobs
	int GetNumBlobs() const 
	{ 
		return(m_blobs.size()); 
	}

    const Blob_vector& getBlobVector(){return m_blobs;}


private:
	myCompLabelerGroup compLabeler;

	//! Funci� per gestionar els errors
	//! Function to manage the errors
	void RaiseError(const int errorCode) const;

	//! Does the Filter method job
	void DoFilter(CBlobResult &dst,
				int filterAction, blobOperator *evaluador, 
				int condition, double lowLimit, double highLimit = 0) const;

protected:
	//! Vector with all the blobs
	Blob_vector		m_blobs;
};

#endif // !defined(_CLASSE_BLOBRESULT_INCLUDED)
