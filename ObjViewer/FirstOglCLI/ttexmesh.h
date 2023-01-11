#pragma once

#pragma warning(disable:4996)

#include "tmath.h"
#include "./OglImage.h"
#include <list>
#include <iostream>
#include <vector>
#include <set>
#include <map>

#include "time.h"



/*
                   + v[0],t[0]
				 / | 
			    /  | 
		e[0]   /   | e[2]
			  /    |
			 /     |
v[1],t[1]   +------+ v[2],t[2]
　　　　　　　e[1]
　　　
*/



class TPoly
{
public:
	int vIdx[3]; 
	int tIdx[3];
	
	int edge[3]; //edgeIdx

    TPoly(int v0=0, int v1=0, int v2=0, int t0=0, int t1=0, int t2=0){ 
		vIdx[0] = v0; vIdx[1] = v1; vIdx[2] = v2;
		tIdx[0] = t0; tIdx[1] = t1; tIdx[2] = t2;
	}
    TPoly(const TPoly &p ){ Set(p); }

	void Set( const TPoly &p){
		memcpy( vIdx, p.vIdx, sizeof( int ) * 3);
		memcpy( tIdx, p.tIdx, sizeof( int ) * 3);
	}

	TPoly& operator= (const TPoly  &v){ Set(v); return *this; }
};




/*
      + v[1]
	  |
	  |
 p[0] | P[1]
	  |
	  |
	  + v[0]

*/
class TEdge
{
public:
	int v[2]; //v0 < v1
	int p[2];
	bool bAtlsSeam; //is seam on the atras?


	TEdge(int v0=-1, int v1=-1)
	{
		v[0] = v0;
		v[1] = v1;
		p[0] = p[1] = -1;
		bAtlsSeam = false;
	}

	TEdge(const TEdge &e ){ Set(e); }
	TEdge& operator= (const TEdge  &e){ Set(e); return *this; }

	void Set( const TEdge &e){
		memcpy( v, e.v, sizeof( int ) * 2);
		memcpy( p, e.p, sizeof( int ) * 2);
		bAtlsSeam = e.bAtlsSeam;
	}




};


inline bool t_intersectRayToTriangle
(
	const EVec3d &rayP,
	const EVec3d &rayD,
	const EVec3d &x0,
	const EVec3d &x1,
	const EVec3d &x2,
	EVec3d &pos
	)
{
	Eigen::Matrix3d A;
	A << x1[0] - x0[0], x2[0] - x0[0], -rayD[0],
		 x1[1] - x0[1], x2[1] - x0[1], -rayD[1],
		 x1[2] - x0[2], x2[2] - x0[2], -rayD[2];

	EVec3d stu = A.inverse()*(rayP - x0);

	if (0 <= stu[0] && stu[0] <= 1 &&
		0 <= stu[1] && stu[1] <= 1 &&
		0 <= stu[0] + stu[1] && stu[0] + stu[1] <= 1)
	{
		pos = rayP + stu[2] * rayD;
		return true;
	}

	return false;
}






class TTexMesh
{
public:

	//Vertex 
	int    m_vSize ;
	EVec3d *m_verts  ;
	EVec3d *m_v_norms;

	std::vector<std::vector<int>> m_v_RingPs;
	std::vector<std::vector<int>> m_v_RingVs;

	//UV coords 
	int m_uvSize;
	EVec3d *m_uvs    ;

	//Polys
	int m_pSize     ;
	TPoly *m_polys  ;
	EVec3d *m_p_norms;

	//Edges
	int m_eSize;
	TEdge *m_edges;


	TTexMesh()
	{
		m_vSize   = 0;
		m_verts   = 0;
		m_v_norms = 0;
	
		m_uvSize  = 0;
		m_uvs     = 0;

		m_pSize   = 0;
		m_polys   = 0;

		m_eSize   = 0;
		m_edges   = 0;
    m_buffers[0] = 0;
    m_buffers[1] = 0;
    m_buffers[2] = 0;
    m_buffers[3] = 0;
    vrtVBO = 0; idxVBO = 0;
	}
	TTexMesh(const TTexMesh &src) { Set(src); }
	TTexMesh& operator=(const TTexMesh &src) { Set(src); return *this; }

	~TTexMesh()
	{
		clear();
	}

	void clear()
	{
		m_vSize  = 0;
		m_uvSize = 0;
		m_pSize  = 0;
		m_eSize  = 0;
		if( m_verts   != 0) delete[] m_verts  ; m_verts = 0;
		if( m_v_norms != 0) delete[] m_v_norms; m_v_norms = 0;
		if( m_uvs     != 0) delete[] m_uvs    ; m_uvs = 0;
		if( m_polys   != 0) delete[] m_polys  ; m_polys = 0;
		if( m_p_norms != 0) delete[] m_p_norms; m_p_norms = 0;
		if( m_edges   != 0) delete[] m_edges  ; m_edges = 0;
	}

	void Set( const TTexMesh &m)
	{
		clear();
		m_vSize = m.m_vSize;
		if (m_vSize != 0)
		{
			m_verts   = new EVec3d[m_vSize];
			m_v_norms = new EVec3d[m_vSize];
			memcpy(m_verts  , m.m_verts  , sizeof(EVec3d)*m_vSize);
			memcpy(m_v_norms, m.m_v_norms, sizeof(EVec3d)*m_vSize);
		}

		m_uvSize  = m.m_uvSize;
		if (m_uvSize != 0)
		{
			m_uvs = new EVec3d[m_uvSize];
			memcpy(m_uvs, m.m_uvs, sizeof(EVec3d)*m_uvSize);
		}

		m_pSize   = m.m_pSize;
		if (m_pSize != 0)
		{
			m_polys = new TPoly[m_pSize];
			memcpy(m_polys, m.m_polys, sizeof(TPoly)*m_pSize);
		}
		m_v_RingPs = m.m_v_RingPs;
		m_v_RingVs = m.m_v_RingVs;

		m_eSize = m.m_eSize;
		if (m_eSize != 0)
		{
			m_edges = new TEdge[m_eSize];
			memcpy(m_edges, m.m_edges, sizeof(TEdge)*m_eSize);
		}
	}


	bool initialize(const char *fName)
	{	
		FILE* fp = fopen(fName,"r") ;
		if( !fp ) return false;

		std::list<EVec3d>  vs_list   , uvs_list;
		std::list<TPoly >  polys_list;


		char buf[512] ;		
		while( fgets(buf,255,fp) )
		{
			char* bkup  = _strdup( buf        );
			char* token =  strtok( buf, " \t" );


			if( stricmp( token,"vt" ) == 0 )
			{ 
				EVec3d vt ;
				sscanf( bkup,"vt %lf %lf",&vt[0], &vt[1] ) ;
				uvs_list.push_back( vt ) ;
			} 
			else if( stricmp( token,"v" ) == 0 )
			{ 
				EVec3d v;
				sscanf( bkup,"v %lf %lf %lf",&v[0],&v[1],&v[2] ) ;
				vs_list.push_back( v ) ;
			} 
			else if( stricmp( token,"f" ) == 0 )
			{
				TPoly p(0,0,0,0,0,0);
				int tmp;

				int vtxnum = sscanf( bkup,"f %d %d %d %d", &p.vIdx[0], &p.vIdx[1], &p.vIdx[2], &tmp) ;//sscanfの返り値は正常に読めたフィールド数 (/が入ったら2フィールドしか読めない)

				//t_info( "(%d %d %d)", p.vIdx[0], p.vIdx[1], p.vIdx[2]);
			
				if( vtxnum < 3 ) vtxnum = sscanf( bkup,"f %d/%d %d/%d %d/%d %d/%d" ,            &p.vIdx[0], &p.tIdx[0],
																								&p.vIdx[1], &p.tIdx[1],
																								&p.vIdx[2], &p.tIdx[2], &tmp, &tmp)/2 ;

				if( vtxnum < 3 ) vtxnum = sscanf( bkup,"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &p.vIdx[0], &p.tIdx[0], &tmp,
																								&p.vIdx[1], &p.tIdx[1], &tmp,
																								&p.vIdx[2], &p.tIdx[2], &tmp, &tmp, &tmp, &tmp)/3 ;
				if( vtxnum < 3 ) vtxnum = sscanf( bkup,"f %d//%d %d//%d %d//%d %d//%d" ,        &p.vIdx[0], &tmp,  
																								&p.vIdx[1], &tmp,
																								&p.vIdx[2], &tmp,  &tmp, &tmp )/2 ;
				--p.vIdx[0]; --p.vIdx[1]; --p.vIdx[2];
				--p.tIdx[0]; --p.tIdx[1]; --p.tIdx[2];
				polys_list  .push_back( p ) ;
			}

			free(bkup) ;
		}
		fclose(fp) ;



		m_vSize   = (int) vs_list   .size();
		m_uvSize  = (int) uvs_list  .size();
		m_pSize   = (int) polys_list.size();
		fprintf(stderr, "loaded object file info : %d %d %d\n", m_vSize, m_uvSize, m_pSize);
	
		m_verts   = new EVec3d[m_vSize ];
		m_v_norms = new EVec3d[m_vSize ];
		m_polys   = new TPoly [m_pSize ];
		m_p_norms = new EVec3d[m_pSize ];
		m_uvs     = new EVec3d[m_uvSize];

		int c = 0;
		for( auto it = vs_list   .begin(); it != vs_list   .end(); ++it) m_verts[c++] = *it;
		c = 0;
		for( auto it = uvs_list  .begin(); it != uvs_list  .end(); ++it) m_uvs  [c++] = *it;
		c = 0;
		for( auto it = polys_list.begin(); it != polys_list.end(); ++it) m_polys[c++] = *it;

		updateEdges   ();
		updateNormal  ();
		updateRingInfo();
		fprintf(stderr, "loaded object file info : %d %d %d\n", m_vSize, m_uvSize, m_pSize);
		return true;
	}



	
	void initialize(std::vector<EVec3d> &Vs, std::vector<EVec3d> &UVs, std::vector<TPoly> &Ps)
	{	
		clear();
		m_vSize   = (int) Vs .size();
		m_verts   = new EVec3d[m_vSize ];
		m_v_norms = new EVec3d[m_vSize ];

		m_pSize   = (int) Ps .size();	
		m_polys   = new TPoly [m_pSize ];
		m_p_norms = new EVec3d[m_pSize ];

		m_uvSize  = (int) UVs.size();
		m_uvs     = new EVec3d[m_uvSize];

		int c = 0;
		for( auto it : Vs ) m_verts[c++] = it;
		c = 0;
		for( auto it : UVs) m_uvs  [c++] = it;
		c = 0;
		for( auto it : Ps ) m_polys[c++] = it;

		updateEdges   ();
		updateNormal  ();
		updateRingInfo();

		fprintf( stderr, "initialize DONE %d %d %d\n", m_vSize, m_pSize, m_uvSize);
	}










	void updateEdges()
	{
		static const int edg_mat[3][2]  = {{0,1},{1,2},{2,0}} ;
		
		std::vector<TEdge> Es; //まだサイズが不明
		std::vector< std::list<int> > emanatingEdges( m_vSize ) ;//list for Eminating edge IDs

		for( int pi = 0; pi < m_pSize; ++pi )
		{
			const int *pVtx = m_polys[pi].vIdx ;
		
			for( int i = 0; i < 3; i++ )
			{
				//edgeを生成: v[0,1], p[0,1], oneEdge, polygon.edge登録
				int v0 = pVtx[ edg_mat[i][0] ] ;
				int v1 = pVtx[ edg_mat[i][1] ] ;
 
				bool bInverted = v0 > v1;
				if( bInverted ) std::swap( v0, v1 );
				
				//find eminating edge
				std::list<int>& emanEs = emanatingEdges[ v0 ] ;
				std::list<int>::iterator it;
				for( it = emanEs.begin() ; it != emanEs.end() ; it++ ) if( Es[*it].v[1] == v1 ) break ;

				// the edge not exixt --> add new one
				if( it == emanEs.end() ){
					Es.push_back( TEdge(v0, v1) ) ;
					emanatingEdges[ v0 ].push_back( (int)Es.size()-1 );
					Es.back().p[bInverted?1:0] = pi;
					m_polys[pi].edge[i] =(int) Es.size()-1;
				}
				else
				{
					Es[*it].p[bInverted?1:0] = pi;
					m_polys[pi].edge[i]      = *it;
				}
			}
		}

		m_eSize = (int)Es.size();
		m_edges = new TEdge[ m_eSize ];
		for( int ei=0; ei < m_eSize; ++ei) 
		{
			//copy
			m_edges[ei] = Es[ei];

			//set bAtlsSeam
			TEdge &e   = m_edges[ei];
			TPoly &pA  = m_polys[e.p[0]];
			TPoly &pB  = m_polys[e.p[1]];
			e.bAtlsSeam = true;

			for (int i = 0; i < 3 && e.bAtlsSeam; ++i)
			for (int j = 0; j < 3 && e.bAtlsSeam; ++j)
			{
				int tA0 = pA.tIdx[ edg_mat[i][0] ];
				int tA1 = pA.tIdx[ edg_mat[i][1] ];
				int tB0 = pB.tIdx[ edg_mat[j][0] ];
				int tB1 = pB.tIdx[ edg_mat[j][1] ];
				if( (tA0 == tB0 && tA1 == tB1) || ( tA0 == tB1 && tA1 == tB0 ) ) e.bAtlsSeam = false;
			}
		}
	}


	void updateNormal()
	{
		for(int i=0; i<m_vSize; ++i) m_v_norms[i].Zero();


		for(int i=0; i<m_pSize; ++i)
		{
			int *idx = m_polys[i].vIdx;
			m_p_norms[i] = (m_verts[ idx[1] ] - m_verts[ idx[0] ]).cross( m_verts[ idx[2] ] - m_verts[ idx[0] ]);

			if( m_p_norms[i].norm() > 0 )
			{
				m_p_norms[i].normalize();
				m_v_norms[ idx[0] ] += m_p_norms[i];
				m_v_norms[ idx[1] ] += m_p_norms[i];
				m_v_norms[ idx[2] ] += m_p_norms[i];
			}
		}

		for(int i=0; i<m_vSize; ++i) m_v_norms[i].normalize();
	}


	
	void updateRingInfo()
	{
		m_v_RingPs.clear();
		m_v_RingVs.clear();
		m_v_RingPs.resize(m_vSize);
		m_v_RingVs.resize(m_vSize);

		for( int i =0; i < m_pSize; ++i)
		{
			int *idx = m_polys[i].vIdx;
			m_v_RingPs[ idx[0] ].push_back(i);
			m_v_RingPs[ idx[1] ].push_back(i);
			m_v_RingPs[ idx[2] ].push_back(i);
			m_v_RingVs[ idx[0] ].push_back(idx[1]);
			m_v_RingVs[ idx[0] ].push_back(idx[2]);
			m_v_RingVs[ idx[1] ].push_back(idx[0]);
			m_v_RingVs[ idx[1] ].push_back(idx[2]);
			m_v_RingVs[ idx[2] ].push_back(idx[0]);
			m_v_RingVs[ idx[2] ].push_back(idx[1]);
		}

 		for (int i = 0; i < m_vSize; ++i) 
		{
			sort  (m_v_RingVs[i].begin(), m_v_RingVs[i].end());
			auto it = unique(m_v_RingVs[i].begin(), m_v_RingVs[i].end());
			m_v_RingVs[i].erase( it, m_v_RingVs[i].end());
		}
	}
		


	void draw( )
	{
		glBegin ( GL_TRIANGLES  );

		const EVec3d *verts = m_verts  ;
		const EVec3d *norms = m_v_norms;
		const EVec3d *uvs   = m_uvs    ;

		for (int i = 0; i < m_pSize; ++i)
		{
			const int *idx   = m_polys[i].vIdx;
			const int *uvIdx = m_polys[i].tIdx;
			glNormal3dv( norms[idx[0] ].data()); glTexCoord2dv( uvs[uvIdx[0]].data()); glVertex3dv( verts[idx[0]].data());
			glNormal3dv( norms[idx[1] ].data()); glTexCoord2dv( uvs[uvIdx[1]].data()); glVertex3dv( verts[idx[1]].data());
			glNormal3dv( norms[idx[2] ].data()); glTexCoord2dv( uvs[uvIdx[2]].data()); glVertex3dv( verts[idx[2]].data());
		}
		glEnd();

		glDisable( GL_TEXTURE_2D );
	}


	void drawEdge( float lineWidth)
	{
		glColor3d(1,1,1);
		glLineWidth( lineWidth );

		glDisable( GL_LIGHTING   );

		glBegin  ( GL_LINES);

		const EVec3d *verts = m_verts  ;

		for (int i = 0; i < m_pSize; ++i)
		{
			const int *idx   = m_polys[i].vIdx;
			glVertex3dv( verts[idx[0]].data()); glVertex3dv( verts[idx[1]].data());
			glVertex3dv( verts[idx[1]].data()); glVertex3dv( verts[idx[2]].data());
			glVertex3dv( verts[idx[2]].data()); glVertex3dv( verts[idx[0]].data());
		}
		glEnd();
	}


  #define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
 

  //速度を評価するための実装//
  GLuint vrtVBO, idxVBO;
  void draw_tmp()
  {
    if( vrtVBO == 0 )
    {
      std::cout << "000\n";

      double vs[12] = { 0, 0, 0,  10, 0, 0,  10, 10, 0,  0, 10, 0 };
      int    id[6]  = { 0, 1, 2,  0, 2, 3 };
      glGenBuffers(1, &vrtVBO);
      glBindBuffer(GL_ARRAY_BUFFER, vrtVBO);
      glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(double), (GLdouble*)&vs[0], GL_STATIC_DRAW);
 
      glGenBuffers(1, &idxVBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxVBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*2*sizeof(int), &id[0], GL_STATIC_DRAW);
    }
    
    std::cout << vrtVBO << "    aa    " << idxVBO << "\n";
    glDisable(GL_LIGHTING);
    glColor3d(1,1,0);

    glBindBuffer(GL_ARRAY_BUFFER, vrtVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxVBO);
 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
    glDisableClientState(GL_VERTEX_ARRAY); 
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }



  GLuint m_buffers[4];
	void drawByVBO( )
	{
    if(m_buffers[0] == 0)
    {

      float *vs = new float[9*m_pSize]; // 3*pize * 3
      float *ns = new float[9*m_pSize]; // 3*pize * 3
      float *ts = new float[6*m_pSize]; // 3*pize * 2
      int    *id = new int   [3*m_pSize];


      for( int p=0; p < m_pSize; ++p)
      {
        const int *vidx = m_polys[p].vIdx;
        const int *tidx = m_polys[p].tIdx;
        for( int i=0; i < 3; ++i){
          vs[9*p+0+i] = (float) m_verts  [vidx[0]][i];
          vs[9*p+3+i] = (float) m_verts  [vidx[1]][i];
          vs[9*p+6+i] = (float) m_verts  [vidx[2]][i];
          ns[9*p+0+i] = (float) m_v_norms[vidx[0]][i];
          ns[9*p+3+i] = (float) m_v_norms[vidx[1]][i];
          ns[9*p+6+i] = (float) m_v_norms[vidx[2]][i];
        }
        ts[6*p+0+0] = (float) m_uvs  [tidx[0]][0];
        ts[6*p+0+1] = (float) m_uvs  [tidx[0]][1];
        ts[6*p+2+0] = (float) m_uvs  [tidx[1]][0];
        ts[6*p+2+1] = (float) m_uvs  [tidx[1]][1];
        ts[6*p+4+0] = (float) m_uvs  [tidx[2]][0];
        ts[6*p+4+1] = (float) m_uvs  [tidx[2]][1];

        id[p*3+0] = p*3+0;
        id[p*3+1] = p*3+1;
        id[p*3+2] = p*3+2;
      }
      

      //init vbo
      glGenBuffers(4, m_buffers);
      //１つ目のバッファオブジェクトに頂点データ配列を転送する 
      glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_pSize*9, vs, GL_STATIC_DRAW);
  
      //２つ目のバッファオブジェクトに法線データ配列を転送する 
      glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_pSize*9, ns, GL_STATIC_DRAW);
  
      //３つ目のバッファオブジェクトにテクスチャ座標配列を転送する 
      glBindBuffer(GL_ARRAY_BUFFER, m_buffers[2]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_pSize*6, ts, GL_STATIC_DRAW);
  
      //４つ目のバッファオブジェクトに頂点のインデックスを転送する 
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[3]);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*m_pSize*3, id, GL_STATIC_DRAW);

      delete[] vs;
      delete[] ns;
      delete[] ts;
      delete[] id;
    }
    //rendering 
    //頂点データ，法線データ，テクスチャ座標の配列を有効にする 
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  
    //頂点データの場所を指定する 
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
    glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
  
    //法線データの場所を指定する 
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
    glNormalPointer(GL_FLOAT, 0, BUFFER_OFFSET(0));
  
    //テクスチャ座標の場所を指定する 
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[2]);
    glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));
  
    //頂点のインデックスの場所を指定して図形を描く 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[3]);
    glDrawElements(GL_TRIANGLES, m_pSize * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
  //頂点データ，法線データ，テクスチャ座標の配列を無効にする 
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    //std::cout <<"fin!!!!!!\n";
}





	void Translate(EVec3d t)
	{
		for( int i=0; i < m_vSize; ++i ) m_verts[i] += t;
	}

	void Scale(double d)
	{
		for( int i=0; i < m_vSize; ++i ) m_verts[i] *= d;
	}



	EVec3d getGravityCenter()
	{
		EVec3d p;
		for( int i=0; i < m_vSize; ++i ) p += m_verts[i];
		return p / (double)m_vSize;
	}



	//compute collision to all polygons ald (p0-p1)
	//ignor back surface (p1-p0) * norm > 0
	bool intersectToLineSegment_ignorBackSurface(const EVec3d &p0, const EVec3d &p1, int ignorVid) const
	{
		EMat3d M;
		EVec3d b, stk, cRay(p1 - p0);

		for (int i = 0; i < m_pSize; ++i)
		{
			if (m_polys[i].vIdx[0] == ignorVid ||
				m_polys[i].vIdx[1] == ignorVid ||
				m_polys[i].vIdx[2] == ignorVid || cRay.dot(m_p_norms[i]) > 0) continue;

			const EVec3d &v0 = m_verts[m_polys[i].vIdx[0]];
			const EVec3d &v1 = m_verts[m_polys[i].vIdx[1]];
			const EVec3d &v2 = m_verts[m_polys[i].vIdx[2]];

			M << v1[0] - v0[0], v2[0] - v0[0], -(p1[0] - p0[0]),
				 v1[1] - v0[1], v2[1] - v0[1], -(p1[1] - p0[1]),
				 v1[2] - v0[2], v2[2] - v0[2], -(p1[2] - p0[2]);

			if (M.determinant() == 0) continue;
			stk = M.partialPivLu().solve( p0 - v0 );

			if (0 <= stk[0] && 0 <= stk[1] && stk[0] + stk[1] <= 1 && 0 <= stk[2] && stk[2] <= 1) return true;
		}


		return false;
	}




	
	bool pickByRay( const EVec3d &rayP, const EVec3d &rayD, EVec3d &pos, int &pIdx ) const
	{
		double depth = DBL_MAX;
		EVec3d tmpPos;
		pIdx  = -1;
		for (int pi = 0; pi < m_pSize; ++pi)
		{
			const int *p = m_polys[pi].vIdx;

			if (t_intersectRayToTriangle( rayP, rayD, m_verts[p[0]], m_verts[p[1]], m_verts[p[2]], tmpPos) )
			{
				double d = (tmpPos - rayP).norm();
				if (d < depth)
				{
					depth = d;
					pos   = tmpPos;
					pIdx  = pi;
				}
			}
		}
		return depth != DBL_MAX;
	}



	void getNringPs(const int pid, const int N, std::set<int> &Ps) const
	{
		Ps.insert(pid);

		for (int k = 0; k < N; ++k)
		{
			std::set<int> tmp = Ps;
			Ps.clear();

			for( const auto it : tmp) 
			{
				int *vidx = m_polys[ it ].vIdx;
				for (int i = 0; i < 3; ++i) 
					for( auto pid : m_v_RingPs[ vidx[i] ] ) Ps.insert( pid );
			}			
		}
	}


};







inline bool intersectTriangleToRayY(
	const EVec3d &v0, 
	const EVec3d &v1, 
	const EVec3d &v2, 
	const double x, 
	const double z, 
	
	double &y //output 
)
{
	//pre-check
	if( (x<v0[0] && x<v1[0] && x<v2[0]) || (x>v0[0] && x>v1[0] && x>v2[0]) ) return false;
	if( (z<v0[2] && z<v1[2] && z<v2[2]) || (z>v0[2] && z>v1[2] && z>v2[2]) ) return false;
				
	double s,t;
	if( !t_SolveLinearEq2d( v1[0]-v0[0], v2[0]-v0[0], 
									v1[2]-v0[2], v2[2]-v0[2], x-v0[0], z-v0[2], s, t) ) return false; 
	if (s < 0 || t < 0 || s+t > 1) return false;

	y = (1-s-t)*v0[1] + s*v1[1] + t*v2[1];
	return true;
}
