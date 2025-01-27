﻿namespace mainForm
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnCOM = new System.Windows.Forms.Button();
            this.gbTemp = new System.Windows.Forms.GroupBox();
            this.btnTChart = new System.Windows.Forms.Button();
            this.lbltmin = new System.Windows.Forms.Label();
            this.lbltavg = new System.Windows.Forms.Label();
            this.lblthigh = new System.Windows.Forms.Label();
            this.btnCLEAR = new System.Windows.Forms.Button();
            this.gbTemp.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnCOM
            // 
            this.btnCOM.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCOM.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnCOM.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.btnCOM.Location = new System.Drawing.Point(12, 12);
            this.btnCOM.Name = "btnCOM";
            this.btnCOM.Size = new System.Drawing.Size(107, 70);
            this.btnCOM.TabIndex = 0;
            this.btnCOM.Text = "COM - OFF";
            this.btnCOM.UseVisualStyleBackColor = true;
            this.btnCOM.Click += new System.EventHandler(this.btnCOM_Click);
            // 
            // gbTemp
            // 
            this.gbTemp.Controls.Add(this.btnTChart);
            this.gbTemp.Controls.Add(this.lbltmin);
            this.gbTemp.Controls.Add(this.lbltavg);
            this.gbTemp.Controls.Add(this.lblthigh);
            this.gbTemp.Font = new System.Drawing.Font("Lucida Fax", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.gbTemp.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.gbTemp.Location = new System.Drawing.Point(147, 12);
            this.gbTemp.Name = "gbTemp";
            this.gbTemp.Size = new System.Drawing.Size(532, 151);
            this.gbTemp.TabIndex = 6;
            this.gbTemp.TabStop = false;
            this.gbTemp.Text = "Temperatura [ºC]";
            // 
            // btnTChart
            // 
            this.btnTChart.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnTChart.ForeColor = System.Drawing.Color.Transparent;
            this.btnTChart.Location = new System.Drawing.Point(104, 76);
            this.btnTChart.Name = "btnTChart";
            this.btnTChart.Size = new System.Drawing.Size(290, 53);
            this.btnTChart.TabIndex = 3;
            this.btnTChart.Text = "Mostrar Grafico Temp";
            this.btnTChart.UseVisualStyleBackColor = true;
            this.btnTChart.Click += new System.EventHandler(this.btnTChart_Click);
            // 
            // lbltmin
            // 
            this.lbltmin.AutoSize = true;
            this.lbltmin.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.lbltmin.Location = new System.Drawing.Point(367, 36);
            this.lbltmin.Name = "lbltmin";
            this.lbltmin.Size = new System.Drawing.Size(111, 24);
            this.lbltmin.TabIndex = 2;
            this.lbltmin.Text = "T_MIN: ...";
            // 
            // lbltavg
            // 
            this.lbltavg.AutoSize = true;
            this.lbltavg.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.lbltavg.Location = new System.Drawing.Point(194, 36);
            this.lbltavg.Name = "lbltavg";
            this.lbltavg.Size = new System.Drawing.Size(116, 24);
            this.lbltavg.TabIndex = 1;
            this.lbltavg.Text = "T_AVG: ...";
            // 
            // lblthigh
            // 
            this.lblthigh.AutoSize = true;
            this.lblthigh.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.lblthigh.Location = new System.Drawing.Point(16, 36);
            this.lblthigh.Name = "lblthigh";
            this.lblthigh.Size = new System.Drawing.Size(116, 24);
            this.lblthigh.TabIndex = 0;
            this.lblthigh.Text = "T_MAX: ...";
            // 
            // btnCLEAR
            // 
            this.btnCLEAR.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCLEAR.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnCLEAR.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.btnCLEAR.Location = new System.Drawing.Point(12, 105);
            this.btnCLEAR.Name = "btnCLEAR";
            this.btnCLEAR.Size = new System.Drawing.Size(107, 70);
            this.btnCLEAR.TabIndex = 8;
            this.btnCLEAR.Text = "LIMPIAR DATOS";
            this.btnCLEAR.UseVisualStyleBackColor = true;
            this.btnCLEAR.Click += new System.EventHandler(this.btnCLEAR_Click);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(694, 190);
            this.Controls.Add(this.btnCLEAR);
            this.Controls.Add(this.gbTemp);
            this.Controls.Add(this.btnCOM);
            this.Name = "mainForm";
            this.Text = "TP_FINAL_EDI2";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_onFormClosing);
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.gbTemp.ResumeLayout(false);
            this.gbTemp.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnCOM;
        private System.Windows.Forms.GroupBox gbTemp;
        private System.Windows.Forms.Label lbltmin;
        private System.Windows.Forms.Label lbltavg;
        private System.Windows.Forms.Label lblthigh;
        private System.Windows.Forms.Button btnTChart;
        private System.Windows.Forms.Button btnCLEAR;
    }
}

